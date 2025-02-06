#ifndef CURSOR_MANAGER_H
#define CURSOR_MANAGER_H

#include <SDL.h>

class CursorManager {
public:
    // Constructor
    CursorManager(int tileSize);

    // Updates cursor position and detects tile changes
    bool update(const SDL_Event& event, int maxCols, int maxRows, int& outX, int& outY);

    // Getters
    int getHoverX() const;
    int getHoverY() const;

private:
    const int TILE_SIZE;
    int hoverTileX = 0;
    int hoverTileY = 0;
};

#endif // CURSOR_MANAGER_H
