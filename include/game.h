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

/**
 * @enum MapState
 * @brief Represents the current state of the game map.
 */
typedef enum MapState {
    INNER, ///< The game is in an inner map view.
    OUTER  ///< The game is in the main world map view.
} MapState;

/**
 * @class Game
 * @brief Manages the core functionality and state of the tile-based game.
 */
class Game {
public:
    /**
     * @brief Constructs the Game object, initializing key components.
     */
    Game();

    /**
     * @brief Destructor for Game, ensuring cleanup of resources.
     */
    ~Game();

    /**
     * @brief Initializes SDL, creates the window, and loads or generates the map.
     * @return True if initialization succeeds, false otherwise.
     */
    bool init();

    /**
     * @brief Starts the main game loop, handling updates, rendering, and events.
     */
    void run();

    /**
     * @brief Cleans up SDL resources and shuts down the game.
     */
    void cleanup();

    void handleTileHover(int mouseX, int mouseY, int hoverX, int hoverY);

    void getMousePosition(int &mouseX, int &mouseY);



private:
    // Game State
    bool running = false;   ///< Flag indicating if the game is running.
    MapState state = OUTER; ///< Current state of the game (inner or outer map).

    // SDL Window & Rendering
    SDL_Window* window = nullptr; ///< The game window.
    std::unique_ptr<RendererManager> rendererManager; ///< Handles rendering.

    // Game Data
    TileMap tileMap;  ///< Manages and stores all tiles in the game.
    CursorManager cursorManager; ///< Manages cursor movement and tile selection.

    // Global Settings
    int TILE_SIZE = 0;  ///< Size of each tile in pixels.
    int WINDOW_WIDTH = 0;  ///< Width of the game window.
    int WINDOW_HEIGHT = 0; ///< Height of the game window.
    std::unordered_map<std::string, std::string> TILE_TEXTURES; ///< Stores tile textures.
    const std::string& MAP_PATH_PREFIX; ///< Path prefix for map files.
    std::string map_filename; ///< Stores the current map filename.
    MapState curr_state = OUTER; ///< Tracks whether the player is in an inner or outer map.

    // Core Game Loop Functions
    /**
     * @brief Processes SDL events, including input handling.
     */
    void processEvents();

    /**
     * @brief Updates the game state (to be implemented).
     */
    void update();

    /**
     * @brief Renders the game scene.
     */
    void render();

    // Inner Map Management
    /**
     * @brief Enters the inner map of a specific tile, saving the current map if needed.
     * @param tile The tile whose inner map is to be entered.
     */
    void enterInnerMap(std::shared_ptr<Tile> tile);

    /**
     * @brief Loads or generates an inner map for a tile.
     * @param tile The tile for which an inner map is needed.
     */
    void generateInnerMap(std::shared_ptr<Tile> tile);

    /**
     * @brief Determines matching terrain types based on the given terrain alias.
     * @param terrainType The alias of the terrain type.
     * @return A vector of matching terrain types.
     */
    std::vector<std::string> getMatchingTerrain(const std::string& terrainType);

    /**
     * @brief Exits the inner map and returns to the outer world.
     */
    void exitInnerMap();
};

#endif // GAME_H
