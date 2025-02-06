#ifndef RENDERER_MANAGER_H
#define RENDERER_MANAGER_H

#include <SDL.h>
#include "TileRenderer.h"
#include <unordered_map>

class RendererManager {
public:
    explicit RendererManager(SDL_Window* window, std::unordered_map<std::string, std::string> tileAssetMap) {
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

        if (!renderer) {
            SDL_Log("Renderer could not be created! SDL Error: %s", SDL_GetError());
            return;
        }

        tileRenderer = new TileRenderer(renderer, tileAssetMap);
    }

    ~RendererManager() {
        delete tileRenderer;
        SDL_DestroyRenderer(renderer);
    }

    void clear() {
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);
    }

    void render(const TileMap& tileMap) { tileRenderer->renderTiles(tileMap, 100); }
    void present() { SDL_RenderPresent(renderer); }

    SDL_Renderer* getSDLRenderer() { return renderer; }  // Access for sub-renderers
    TileRenderer* getTileRenderer() { return tileRenderer; }  // Access to TileRenderer

private:
    SDL_Renderer* renderer;
    TileRenderer* tileRenderer;

    
};

#endif // RENDERER_MANAGER_H
