#ifndef CURSOR_MANAGER_H
#define CURSOR_MANAGER_H

#include <SDL.h>

/**
 * @class CursorManager
 * @brief Manages cursor position and tile selection in a tile-based grid.
 */
class CursorManager {
public:
    /**
     * @brief Constructs a CursorManager with a specified tile size.
     * @param tileSize The size of each tile in pixels.
     */
    CursorManager(int tileSize);

    /**
     * @brief Updates the cursor position and detects if it moves to a new tile.
     * 
     * @param event The SDL event containing mouse movement data.
     * @param maxCols The maximum number of columns in the grid.
     * @param maxRows The maximum number of rows in the grid.
     * @param outX Output parameter storing the new tile X coordinate if changed.
     * @param outY Output parameter storing the new tile Y coordinate if changed.
     * @return True if the cursor moved to a new tile, false otherwise.
     */
    bool update(const SDL_Event& event, int maxCols, int maxRows, int& outX, int& outY);

    /**
     * @brief Gets the current hovered tile's X coordinate.
     * @return The X coordinate of the hovered tile, or -1 if out of bounds.
     */
    int getHoverX() const;

    /**
     * @brief Gets the current hovered tile's Y coordinate.
     * @return The Y coordinate of the hovered tile, or -1 if out of bounds.
     */
    int getHoverY() const;

private:
    const int TILE_SIZE; ///< The size of each tile in pixels.
    int hoverTileX = 0;  ///< Current hovered tile's X coordinate.
    int hoverTileY = 0;  ///< Current hovered tile's Y coordinate.
};

#endif // CURSOR_MANAGER_H
