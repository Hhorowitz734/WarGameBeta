#include "TileRenderer.h"

// Constructor
TileRenderer::TileRenderer(SDL_Renderer* renderer, const std::unordered_map<std::string, std::string>& assetMap)
    : renderer(renderer), assetMap(assetMap) {
    loadTextures();
}

// Destructor
TileRenderer::~TileRenderer() {
    cleanupTextures();
}

// Renders tiles to the screen
void TileRenderer::renderTiles(const TileMap& tileMap, int tileSize) {
    const auto& tiles = tileMap.getTileMap();

    for (const auto& tile : tiles) {
        auto it = textureCache.find(tile.getAssetAlias());
        if (it == textureCache.end() || !it->second) continue;

        SDL_Rect dstRect = { tile.getX(), tile.getY(), tileSize, tileSize };
        SDL_RenderCopy(renderer, it->second, nullptr, &dstRect);
    }
}

// Loads textures from asset map
void TileRenderer::loadTextures() {
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

        textureCache[pair.first] = texture;
    }
}

// Retrieves a texture from the cache
SDL_Texture* TileRenderer::getTexture(const std::string& alias) const {
    auto it = textureCache.find(alias);
    if (it != textureCache.end()) {
        return it->second;
    }
    SDL_Log("Warning: Texture alias '%s' not found!", alias.c_str());
    return nullptr;
}

// Cleans up all loaded textures
void TileRenderer::cleanupTextures() {
    for (auto& pair : textureCache) {
        SDL_DestroyTexture(pair.second);
    }
    textureCache.clear();
}
