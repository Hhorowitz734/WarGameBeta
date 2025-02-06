#include "CursorManager.h"

// Constructor
CursorManager::CursorManager(int tileSize) 
    : TILE_SIZE(tileSize), hoverTileX(-1), hoverTileY(-1) {}

// Updates cursor position and detects tile changes
bool CursorManager::update(const SDL_Event& event, int maxCols, int maxRows, int& outX, int& outY) {
    int oldHoverX = hoverTileX;
    int oldHoverY = hoverTileY;

    if (event.type == SDL_MOUSEMOTION) {
        hoverTileX = event.motion.x / TILE_SIZE;
        hoverTileY = event.motion.y / TILE_SIZE;
    }

    // Reset hover if cursor is outside valid tiles
    if (hoverTileX < 0 || hoverTileX >= maxCols || hoverTileY < 0 || hoverTileY >= maxRows) {
        hoverTileX = -1;
        hoverTileY = -1;
        return false;
    }

    // Update only if cursor moved to a new tile
    if (oldHoverX != hoverTileX || oldHoverY != hoverTileY) {
        outX = hoverTileX;
        outY = hoverTileY;
        return true;
    }

    return false;
}

// Getters
int CursorManager::getHoverX() const { return hoverTileX; }
int CursorManager::getHoverY() const { return hoverTileY; }
