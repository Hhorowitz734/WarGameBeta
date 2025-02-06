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
    // Constructor & Destructor
    TileRenderer(SDL_Renderer* renderer, const std::unordered_map<std::string, std::string>& assetMap);
    ~TileRenderer();

    // Rendering
    void renderTiles(const TileMap& tileMap, int tileSize);

private:
    SDL_Renderer* renderer;
    std::unordered_map<std::string, std::string> assetMap;
    std::unordered_map<std::string, SDL_Texture*> textureCache;

    // Texture management
    void loadTextures();
    SDL_Texture* getTexture(const std::string& alias) const;
    void cleanupTextures();
};

#endif // TILE_RENDERER_H
