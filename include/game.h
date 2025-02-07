#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <filesystem>

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
    std::string map_filename;
    MapState curr_state = OUTER;


    // Core Game Loop Functions
    void processEvents();
    void update();
    void render();

    // Inner Map Stuff
    void enterInnerMap(std::shared_ptr<Tile> tile);
    void generateInnerMap(std::shared_ptr<Tile> tile); // Given a tile, sees if it has an inner map. if it does, loads it. otherwise generates it
    // I feel liike this function should be moved to settings??
    std::vector<std::string> getMatchingTerrain(const std::string& terrainType);
    void exitInnerMap();


};

#endif // GAME_H
