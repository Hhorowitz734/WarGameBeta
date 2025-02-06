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
    tileMap.generateTiles(numRows, numCols, TILE_SIZE, {"medgrass2", "medgrass1", "darkgrass", "deadgrass1", "deadgrass2", "deadgrass3"}); 

    tileMap.saveToFile("test.dat", MAP_PATH_PREFIX);
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