#include "Game.h"

// CONSTRUCTORS + DESTRUCTORS

Game::Game() 
    : window(nullptr), 
    rendererManager(nullptr), 
    running(false), 
    cursorManager(GlobalSettings::getInstance().getTileSize()),
    MAP_PATH_PREFIX(GlobalSettings::getInstance().getMapPathPrefix()) 

    
    {

    // Get global settings
    const GlobalSettings& settings = GlobalSettings::getInstance();
    TILE_SIZE = settings.getTileSize();
    WINDOW_WIDTH = settings.getWindowWidth();
    WINDOW_HEIGHT = settings.getWindowHeight();
    TILE_TEXTURES = settings.getTileTextures();
}


Game::~Game() {
    cleanup();
}





bool Game::init() {

    std::string mapFile;

    // Initialize window
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL could not initialize! SDL Error: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
        "Tile Game", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        WINDOW_WIDTH, 
        WINDOW_HEIGHT, 
        SDL_WINDOW_SHOWN);

    if (!window) {
        SDL_Log("Window could not be created! SDL Error: %s", SDL_GetError());
        return false;
    }

    // Initialize RenderManager
    rendererManager = std::make_unique<RendererManager>(window, TILE_TEXTURES, TILE_SIZE);
    int numRows = WINDOW_HEIGHT / TILE_SIZE;
    int numCols = WINDOW_WIDTH / TILE_SIZE;



#if defined(LOAD_EXISTING_MAP)
    // Load existing map from file
    mapFile = MAP_FILE_PATH;
    tileMap.loadFromFile(mapFile, MAP_PATH_PREFIX);
    SDL_Log("Loaded existing map: %s", mapFile.c_str());

#elif defined(NEW_GAME_MAP)
    // Generate a new map and save it
    mapFile = MAP_FILE_PATH;
    tileMap.generateTiles(numRows, numCols, TILE_SIZE, 
        {"medgrass2", "medgrass1", "darkgrass", "deadgrass1", "deadgrass2", "deadgrass3"});
    tileMap.saveToFile(mapFile, MAP_PATH_PREFIX);
    SDL_Log("Generated new map: %s", mapFile.c_str());

#else
    // Fallback: Default behavior
    mapFile = "default_map.dat";
    tileMap.generateTiles(numRows, numCols, TILE_SIZE, 
        {"medgrass2", "medgrass1", "darkgrass", "deadgrass1", "deadgrass2", "deadgrass3"});
    tileMap.saveToFile(mapFile, MAP_PATH_PREFIX);
    SDL_Log("No map mode selected. Defaulting to: %s", mapFile.c_str());
#endif


    SDL_Log("Using map: %s", mapFile.c_str());
    running = true;
    return true;
}



void Game::run() {
    while (running) {
        update();
        render();
        processEvents();
    }
}


void Game::cleanup() {
    if (window) SDL_DestroyWindow(window);
    SDL_Quit();
}


void Game::processEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
        if (event.type == SDL_MOUSEMOTION) {
            int hoverX, hoverY;
            if (cursorManager.update(event, WINDOW_WIDTH / TILE_SIZE, WINDOW_HEIGHT / TILE_SIZE, hoverX, hoverY)) {


                std::shared_ptr<Tile> tile = tileMap.getTileAt(event.motion.x, event.motion.y);
                const GlobalSettings& settings = GlobalSettings::getInstance();
                SDL_Color color;

                if (settings.isPlayerId(tile->getOwnerId())) { color = {0, 255, 0, 125}; }
                else { color = {255, 255, 0, 125}; }

                rendererManager->updateHover(hoverX, hoverY, color); // Send coordinates directly
            }

        }
        if (event.type == SDL_MOUSEBUTTONDOWN) {

            std::shared_ptr<Tile> tile = tileMap.getTileAt(event.motion.x, event.motion.y);
            enterInnerMap(tile);
            
        }
    }
}


void Game::update() {
    // DO LATER
}


void Game::render() {
    rendererManager->clear();
    rendererManager->render(tileMap); 
    rendererManager->present();
}

void Game::enterInnerMap(std::shared_ptr<Tile> tile) {
    if (!tile) {
        std::cerr << "Error: Null tile passed to enterInnerMap.\n";
        return;
    }

    // Save the current map state only if MAP_FILE_PATH is defined
    #ifdef MAP_FILE_PATH
        tileMap.saveToFile(MAP_FILE_PATH, MAP_PATH_PREFIX);
    #else
        std::cerr << "Warning: MAP_FILE_PATH is not defined, using default map file.\n";
        tileMap.saveToFile("default_map.dat", MAP_PATH_PREFIX);
    #endif

    // Generate the inner map based on game mode
    std::vector<std::string> terrainTypes;

    generateInnerMap(tile);
}


void Game::generateInnerMap(std::shared_ptr<Tile> tile) {
    if (!tile) {
        std::cerr << "Error: Null tile passed to generateInnerMap.\n";
        return;
    }

    // Define the base map file name, using MAP_FILE_PATH if defined
    #ifdef MAP_FILE_PATH
        std::string mapName = MAP_FILE_PATH;
    #else
        std::string mapName = "default_map.dat"; // Default map file if MAP_FILE_PATH is not defined
    #endif

    // Remove the ".dat" extension from MAP_FILE_PATH
    size_t pos = mapName.rfind(".dat");
    if (pos != std::string::npos) {
        mapName = mapName.substr(0, pos);  // Strip the extension
    }

    // Construct the full path for the inner map
    std::string innerMapFile = MAP_PATH_PREFIX + mapName + "/tile_" + 
                               std::to_string(tile->getX()) + "_" + 
                               std::to_string(tile->getY()) + ".dat";

    // Check if the inner map file exists
    if (std::filesystem::exists(innerMapFile)) {
        std::cout << "Loading inner map from " << innerMapFile << "\n";
        tileMap.loadFromFile(innerMapFile, MAP_PATH_PREFIX);
        return;
    } 

    std::cout << "Generating new inner map for tile (" << tile->getX() << ", " << tile->getY() << ")\n";

    // Generate a new inner map
    tileMap.generateTiles(WINDOW_HEIGHT / TILE_SIZE, WINDOW_WIDTH / TILE_SIZE, TILE_SIZE, 
        getMatchingTerrain(tile->getAssetAlias()));

    // Ensure directory exists before saving
    std::filesystem::create_directories(MAP_PATH_PREFIX + mapName);

    // Save the generated inner map
    tileMap.saveToFile(innerMapFile, MAP_PATH_PREFIX);
    
}


std::vector<std::string> Game::getMatchingTerrain(const std::string& terrainType) {
    if (terrainType == "darkgrass") {
        return {"darkgrass"};
    } else if (terrainType == "medgrass1" || terrainType == "medgrass2") {
        return {"medgrass1", "medgrass2"};
    } else if (terrainType == "deadgrass1" || terrainType == "deadgrass2" || terrainType == "deadgrass3") {
        return {"deadgrass1", "deadgrass2", "deadgrass3"};
    } else {
        return {"darkgrass"}; // Default case
    }
}
