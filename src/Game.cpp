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
                rendererManager->updateHover(hoverX, hoverY); // Send coordinates directly
            }

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