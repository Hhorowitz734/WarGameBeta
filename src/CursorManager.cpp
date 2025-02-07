#include "CursorManager.h"

// Constructor: Initializes the cursor manager with a tile size.
CursorManager::CursorManager(int tileSize) 
    : TILE_SIZE(tileSize), hoverTileX(-1), hoverTileY(-1) {}

// Updates cursor position and detects if it moves to a new tile.
bool CursorManager::update(const SDL_Event& event, int maxCols, int maxRows, int& outX, int& outY) {
    int oldHoverX = hoverTileX;
    int oldHoverY = hoverTileY;

    if (event.type == SDL_MOUSEMOTION) {
        hoverTileX = event.motion.x / TILE_SIZE;
        hoverTileY = event.motion.y / TILE_SIZE;
    }

    // Reset hover coordinates if cursor moves outside valid tile bounds.
    if (hoverTileX < 0 || hoverTileX >= maxCols || hoverTileY < 0 || hoverTileY >= maxRows) {
        hoverTileX = -1;
        hoverTileY = -1;
        return false;
    }

    // Return true if the cursor moved to a new tile.
    if (oldHoverX != hoverTileX || oldHoverY != hoverTileY) {
        outX = hoverTileX;
        outY = hoverTileY;
        return true;
    }

    return false;
}

// Getters for the current hovered tile coordinates.
int CursorManager::getHoverX() const { 
    return hoverTileX; 
}

int CursorManager::getHoverY() const { 
    return hoverTileY; 
}
