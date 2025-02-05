#ifndef TILE_RENDERER_H
#define TILE_RENDERER_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Tile.h"
#include "TileMap.h"

#include <iostream>

class TileRenderer {
public:
    explicit TileRenderer(SDL_Renderer* renderer)
        : renderer(renderer) {}

    ~TileRenderer() {}

    void renderTiles(const TileMap& tileMap, int tileSize) {
        const auto& tiles = tileMap.getTileMap(); // Get tiles from TileMap


        for (const auto& row : tiles) {
            for (const auto& tile : row) {
                SDL_Surface* surface = IMG_Load(tile.getAssetPath().c_str());
                if (!surface) {
                    SDL_Log("Failed to load tile texture: %s", IMG_GetError());
                    continue;
                }

                SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
                SDL_FreeSurface(surface);

                if (!texture) continue;

                SDL_Rect dstRect = { tile.getX(), tile.getY(), tileSize, tileSize };
                SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
                SDL_DestroyTexture(texture);
            }
        }
    }

private:
    SDL_Renderer* renderer;
};

#endif // TILE_RENDERER_H
