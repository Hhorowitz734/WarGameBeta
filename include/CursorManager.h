#ifndef CURSOR_MANAGER
#define CURSOR_MANAGER

#include <tuple>

class CursorManager {
public:

    CursorManager(int tileSize) : TILE_SIZE(tileSize), hoverTileX(-1), hoverTileY(-1) {};

    std::tuple<int, int> update(const SDL_Event& event) {
        int oldHoverX = hoverTileX;
        int oldHoverY = hoverTileY;

        if (event.type == SDL_MOUSEMOTION) {
            hoverTileX = event.motion.x / TILE_SIZE;
            hoverTileY = event.motion.y / TILE_SIZE;
        }

        if (oldHoverX == hoverTileX && oldHoverY == hoverTileY) {
            return std::make_tuple(-1, -1); // No change, return invalid hover
        }

        return std::make_tuple(hoverTileX, hoverTileY);
    }


    int getHoverX() const { return hoverTileX; }
    int getHoverY() const { return hoverTileY; }

private:

    const int TILE_SIZE;
    int hoverTileX, hoverTileY = 0;
};


#endif