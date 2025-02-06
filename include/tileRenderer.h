#ifndef TILE_RENDERER_H
#define TILE_RENDERER_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <unordered_map>
#include "Tile.h"
#include "TileMap.h"

class TileRenderer {
public:
    explicit TileRenderer(SDL_Renderer* renderer, const std::unordered_map<std::string, std::string>& assetMap)
        : renderer(renderer), assetMap(assetMap) {
        loadTextures(); // ✅ Load textures once
    }

    ~TileRenderer() {
        cleanupTextures(); // ✅ Free textures at destruction
    }

    void renderTiles(const TileMap& tileMap, int tileSize) {
        const auto& tiles = tileMap.getTileMap(); 

        for (const auto& row : tiles) {
            for (const auto& tile : row) {
                std::string assetAlias = tile.getAssetAlias();
                SDL_Texture* texture = getTexture(assetAlias);

                if (!texture) continue;

                SDL_Rect dstRect = { tile.getX(), tile.getY(), tileSize, tileSize };
                SDL_RenderCopy(renderer, texture, nullptr, &dstRect);
            }
        }
    }

private:
    SDL_Renderer* renderer;
    std::unordered_map<std::string, std::string> assetMap;
    std::unordered_map<std::string, SDL_Texture*> textureCache; // ✅ Cache textures

    void loadTextures() {
        for (const auto& pair : assetMap) {
            SDL_Surface* surface = IMG_Load(pair.second.c_str());
            if (!surface) {
                SDL_Log("Failed to load texture: %s", IMG_GetError());
                continue;
            }

            SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
            SDL_FreeSurface(surface);

            if (!texture) {
                SDL_Log("Failed to create texture for: %s", pair.second.c_str());
                continue;
            }

            textureCache[pair.first] = texture; // ✅ Store in cache
        }
    }

    SDL_Texture* getTexture(const std::string& alias) const {
        auto it = textureCache.find(alias);
        if (it != textureCache.end()) {
            return it->second;
        }
        SDL_Log("Warning: Texture alias '%s' not found!", alias.c_str());
        return nullptr;
    }

    void cleanupTextures() {
        for (auto& pair : textureCache) {
            SDL_DestroyTexture(pair.second);
        }
        textureCache.clear();
    }
};

#endif // TILE_RENDERER_H
