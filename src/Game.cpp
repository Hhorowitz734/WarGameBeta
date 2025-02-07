#include "Game.h"

// CONSTRUCTORS + DESTRUCTORS

// Default constructor: Initializes game settings and state.
Game::Game() 
    : window(nullptr), 
      rendererManager(nullptr), 
      running(false), 
      cursorManager(GlobalSettings::getInstance().getTileSize()),
      MAP_PATH_PREFIX(GlobalSettings::getInstance().getMapPathPrefix()) {
    
    // Load global settings
    const GlobalSettings& settings = GlobalSettings::getInstance();
    TILE_SIZE = settings.getTileSize();
    WINDOW_WIDTH = settings.getWindowWidth();
    WINDOW_HEIGHT = settings.getWindowHeight();
    TILE_TEXTURES = settings.getTileTextures();
}

// Destructor: Cleans up resources.
Game::~Game() {
    cleanup();
}

// Initializes SDL, creates the window, and loads or generates the map.
bool Game::init() {
    std::string mapFile;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL Error: %s", SDL_GetError());
        return false;
    }

    // Create game window
    window = SDL_CreateWindow(
        "Tile Game", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        WINDOW_WIDTH, 
        WINDOW_HEIGHT, 
        SDL_WINDOW_SHOWN
    );

    if (!window) {
        SDL_Log("Window could not be created! SDL Error: %s", SDL_GetError());
        return false;
    }

    // Initialize RenderManager
    rendererManager = std::make_unique<RendererManager>(window, TILE_TEXTURES, TILE_SIZE);
    int numRows = WINDOW_HEIGHT / TILE_SIZE;
    int numCols = WINDOW_WIDTH / TILE_SIZE;

    // Load or generate the map
    #if defined(LOAD_EXISTING_MAP)
        mapFile = MAP_FILE_PATH;
        tileMap.loadFromFile(mapFile, MAP_PATH_PREFIX);
        SDL_Log("Loaded existing map: %s", mapFile.c_str());

    #elif defined(NEW_GAME_MAP)
        mapFile = MAP_FILE_PATH;
        tileMap.generateTiles(numRows, numCols, TILE_SIZE, 
            {"medgrass2", "medgrass1", "darkgrass", "deadgrass1", "deadgrass2", "deadgrass3"});
        tileMap.saveToFile(mapFile, MAP_PATH_PREFIX);
        SDL_Log("Generated new map: %s", mapFile.c_str());

    #else
        mapFile = "default_map.dat";
        tileMap.generateTiles(numRows, numCols, TILE_SIZE, 
            {"medgrass2", "medgrass1", "darkgrass", "deadgrass1", "deadgrass2", "deadgrass3"});
        tileMap.saveToFile(mapFile, MAP_PATH_PREFIX);
        SDL_Log("No map mode selected. Defaulting to: %s", mapFile.c_str());
    #endif

    SDL_Log("Using map: %s", mapFile.c_str());
    map_filename = mapFile;
    running = true;
    return true;
}

// Main game loop: Updates, renders, and processes events.
void Game::run() {
    while (running) {
        update();
        render();
        processEvents();
    }
}

// Cleans up SDL resources.
void Game::cleanup() {
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}

// Processes SDL events such as quitting, mouse movement, and key presses.
void Game::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }

        // Handle mouse movement
        if (event.type == SDL_MOUSEMOTION) {
            int hoverX, hoverY;
            if (cursorManager.update(event, WINDOW_WIDTH / TILE_SIZE, WINDOW_HEIGHT / TILE_SIZE, hoverX, hoverY)) {
                std::shared_ptr<Tile> tile = tileMap.getTileAt(event.motion.x, event.motion.y);
                const GlobalSettings& settings = GlobalSettings::getInstance();
                SDL_Color color = settings.isPlayerId(tile->getOwnerId()) ? SDL_Color{0, 255, 0, 125} : SDL_Color{255, 255, 0, 125};
                rendererManager->updateHover(hoverX, hoverY, color);
            }
        }

        // Handle mouse click
        if (event.type == SDL_MOUSEBUTTONDOWN) {
            std::shared_ptr<Tile> tile = tileMap.getTileAt(event.motion.x, event.motion.y);
            if (GlobalSettings::getInstance().isPlayerId(tile->getOwnerId())) {
                enterInnerMap(tile);
            }
        }

        // Handle tab key press to exit inner map
        if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_TAB) {
            exitInnerMap();
        }
    }
}

// Game state update (currently not implemented).
void Game::update() {
    // DO LATER
}

// Renders the game scene.
void Game::render() {
    rendererManager->clear();
    rendererManager->render(tileMap); 
    rendererManager->present();
}

// Handles entering an inner map from a tile.
void Game::enterInnerMap(std::shared_ptr<Tile> tile) {
    if (curr_state == INNER || !tile) {
        return;
    }

    // Save current map state before switching
    #ifdef MAP_FILE_PATH
        tileMap.saveToFile(MAP_FILE_PATH, MAP_PATH_PREFIX);
    #else
        std::cerr << "Warning: MAP_FILE_PATH is not defined, using default map file.\n";
        tileMap.saveToFile("default_map.dat", MAP_PATH_PREFIX);
    #endif

    generateInnerMap(tile);
    curr_state = INNER;
}

// Generates an inner map for a tile, either loading from file or creating a new one.
void Game::generateInnerMap(std::shared_ptr<Tile> tile) {
    if (!tile) {
        std::cerr << "Error: Null tile passed to generateInnerMap.\n";
        return;
    }

    // Determine base map filename
    #ifdef MAP_FILE_PATH
        std::string mapName = MAP_FILE_PATH;
    #else
        std::string mapName = "default_map.dat";
    #endif

    // Strip ".dat" extension
    size_t pos = mapName.rfind(".dat");
    if (pos != std::string::npos) {
        mapName = mapName.substr(0, pos);
    }

    // Construct full path for inner map
    std::string innerMapFile = MAP_PATH_PREFIX + mapName + "/tile_" + 
                               std::to_string(tile->getX()) + "_" + 
                               std::to_string(tile->getY()) + ".dat";

    // Load existing inner map if available
    if (std::filesystem::exists(innerMapFile)) {
        std::cout << "Loading inner map from " << innerMapFile << "\n";
        tileMap.loadFromFile(innerMapFile, MAP_PATH_PREFIX);
        return;
    } 

    std::cout << "Generating new inner map for tile (" << tile->getX() << ", " << tile->getY() << ")\n";

    // Generate new inner map
    tileMap.generateTiles(WINDOW_HEIGHT / TILE_SIZE, WINDOW_WIDTH / TILE_SIZE, TILE_SIZE, 
        getMatchingTerrain(tile->getAssetAlias()));

    // Ensure the directory exists before saving
    std::filesystem::create_directories(MAP_PATH_PREFIX + mapName);

    // Save the generated inner map
    tileMap.saveToFile(innerMapFile, MAP_PATH_PREFIX);
}

// Returns terrain types matching the given terrain alias.
std::vector<std::string> Game::getMatchingTerrain(const std::string& terrainType) {
    if (terrainType == "darkgrass") return {"darkgrass"};
    if (terrainType == "medgrass1" || terrainType == "medgrass2") return {"medgrass1", "medgrass2"};
    if (terrainType == "deadgrass1" || terrainType == "deadgrass2" || terrainType == "deadgrass3") 
        return {"deadgrass1", "deadgrass2", "deadgrass3"};
    return {"darkgrass"}; // Default case
}

// Exits the inner map and reloads the outer map.
void Game::exitInnerMap() {
    if (curr_state == OUTER) return;
    tileMap.loadFromFile(map_filename, MAP_PATH_PREFIX);
    curr_state = OUTER;
}
