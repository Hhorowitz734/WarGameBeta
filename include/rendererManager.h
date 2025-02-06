#ifndef RENDERER_MANAGER_H
#define RENDERER_MANAGER_H

#include <SDL.h>
#include <unordered_map>
#include <tuple>
#include "TileRenderer.h"
#include "TileMap.h"

class RendererManager {
public:
    // Constructor & Destructor
    RendererManager(SDL_Window* window, const std::unordered_map<std::string, std::string>& tileAssetMap, int tileSize);
    ~RendererManager();

    // Rendering
    void clear();
    void render(const TileMap& tileMap);
    void present();

    // Hover state
    void updateHover(int x, int y);

    // Accessors
    SDL_Renderer* getSDLRenderer();
    TileRenderer* getTileRenderer();

private:
    SDL_Renderer* renderer;
    TileRenderer* tileRenderer;
    const int TILE_SIZE;
    std::tuple<int, int> currHover;
};

#endif // RENDERER_MANAGER_H
