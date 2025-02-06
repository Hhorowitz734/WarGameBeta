#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>
#include <memory>
#include <unordered_map>

// Game Components
#include "RendererManager.h"
#include "TileMap.h"
#include "GlobalSettings.h"
#include "CursorManager.h"

typedef enum MapState {
    INNER,
    OUTER
} MapState;

class Game {
public:
    // Constructors & Destructor
    Game();
    ~Game();

    // Core Functions
    bool init();
    void run();
    void cleanup();

    // State machine switch
    

private:
    // Game State
    bool running = false;
    MapState state = OUTER;

    // SDL Window & Rendering
    SDL_Window* window = nullptr;
    std::unique_ptr<RendererManager> rendererManager;

    // Game Data
    TileMap tileMap;  // Owns all tiles
    CursorManager cursorManager;

    // Global Settings 
    int TILE_SIZE = 0;
    int WINDOW_WIDTH = 0;
    int WINDOW_HEIGHT = 0;
    std::unordered_map<std::string, std::string> TILE_TEXTURES;
    const std::string& MAP_PATH_PREFIX;


    // Core Game Loop Functions
    void processEvents();
    void update();
    void render();
};

#endif // GAME_H
