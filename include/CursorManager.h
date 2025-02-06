#ifndef CURSOR_MANAGER
#define CURSOR_MANAGER

#include <tuple>

class CursorManager {
public:

    CursorManager(int tileSize) : TILE_SIZE(tileSize), hoverTileX(-1), hoverTileY(-1) {};

    bool update(const SDL_Event& event, int maxCols, int maxRows, int& outX, int& outY) {
        int oldHoverX = hoverTileX;
        int oldHoverY = hoverTileY;

        if (event.type == SDL_MOUSEMOTION) {
            hoverTileX = event.motion.x / TILE_SIZE;
            hoverTileY = event.motion.y / TILE_SIZE;
        }

        // If cursor is outside valid tiles, reset hover and return false
        if (hoverTileX < 0 || hoverTileX >= maxCols || hoverTileY < 0 || hoverTileY >= maxRows) {
            hoverTileX = -1;
            hoverTileY = -1;
            return false;
        }

        // If position changed, pass new coordinates to Game
        if (oldHoverX != hoverTileX || oldHoverY != hoverTileY) {
            outX = hoverTileX;
            outY = hoverTileY;
            return true;
        }

        return false; // No change, don't update
    }



    int getHoverX() const { return hoverTileX; }
    int getHoverY() const { return hoverTileY; }

private:

    const int TILE_SIZE;
    int hoverTileX, hoverTileY = 0;
};


#endif