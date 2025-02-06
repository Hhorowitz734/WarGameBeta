#ifndef RENDERER_MANAGER_H
#define RENDERER_MANAGER_H

#include <SDL.h>
#include "TileRenderer.h"
#include <unordered_map>
#include <tuple>

#include <iostream>

class RendererManager {
public:
    explicit RendererManager(SDL_Window* window, std::unordered_map<std::string, std::string> tileAssetMap, int tileSize)
    : TILE_SIZE(tileSize) {
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

    void render(const TileMap& tileMap) { 

        tileRenderer->renderTiles(tileMap, TILE_SIZE); 

        
        SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);  
        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 150); 
        SDL_Rect newRect = { std::get<0>(currHover) * TILE_SIZE ,std::get<1>(currHover) * TILE_SIZE, TILE_SIZE, TILE_SIZE };
        SDL_RenderFillRect(renderer, &newRect);
        
    }

    void updateHover(std::tuple<int, int> newHover) { currHover = newHover; }



    void present() { SDL_RenderPresent(renderer); }

    SDL_Renderer* getSDLRenderer() { return renderer; }  // Access for sub-renderers
    TileRenderer* getTileRenderer() { return tileRenderer; }  // Access to TileRenderer

private:
    SDL_Renderer* renderer;
    TileRenderer* tileRenderer;

    int TILE_SIZE = 50;

    std::tuple<int, int> currHover = std::make_tuple(-1, -1); // Track last hover position


    
};

#endif // RENDERER_MANAGER_H
