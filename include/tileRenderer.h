#ifndef TILE_RENDERER_H
#define TILE_RENDERER_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include "Tile.h"
#include "TileMap.h"

#include <iostream>
#include <unordered_map>

class TileRenderer {
public:
    explicit TileRenderer(SDL_Renderer* renderer, std::unordered_map<std::string, std::string> assetMap)
        : renderer(renderer), assetMap(assetMap) {}

    ~TileRenderer() {}

    void renderTiles(const TileMap& tileMap, int tileSize) {
        const auto& tiles = tileMap.getTileMap(); // Get tiles from TileMap


        for (const auto& row : tiles) {
            for (const auto& tile : row) {

                std::string assetAlias = tile.getAssetAlias();
                std::string assetPath = getTilePathFromAlias(assetAlias);

                SDL_Surface* surface = IMG_Load(assetPath.c_str());
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
    std::unordered_map<std::string, std::string> assetMap;

    std::string getTilePathFromAlias(const std::string alias) const {
        auto it = assetMap.find(alias);
        return (it != assetMap.end()) ? it->second : "";
    }
};

#endif // TILE_RENDERER_H
