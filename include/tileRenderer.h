#ifndef TILE_RENDERER_H
#define TILE_RENDERER_H

#include <SDL.h>
#include <SDL_image.h>
#include <vector>
#include <unordered_map>
#include "Tile.h"
#include "TileMap.h"

/**
 * @class TileRenderer
 * @brief Handles rendering of tiles using textures loaded from an asset map.
 */
class TileRenderer {
public:
    /**
     * @brief Constructs a TileRenderer and loads tile textures.
     * @param renderer The SDL renderer used for rendering.
     * @param assetMap A map associating tile asset aliases with file paths.
     */
    TileRenderer(SDL_Renderer* renderer, const std::unordered_map<std::string, std::string>& assetMap);

    /**
     * @brief Destructor that cleans up loaded textures.
     */
    ~TileRenderer();

    /**
     * @brief Renders the tiles from the tile map onto the screen.
     * @param tileMap The tile map containing the tiles to be rendered.
     * @param tileSize The size of each tile in pixels.
     */
    void renderTiles(const TileMap& tileMap, int tileSize);

private:
    SDL_Renderer* renderer; ///< The SDL renderer used for rendering.
    std::unordered_map<std::string, std::string> assetMap; ///< Maps tile aliases to texture file paths.
    std::unordered_map<std::string, SDL_Texture*> textureCache; ///< Caches loaded textures for rendering.

    /**
     * @brief Loads textures from the asset map into the texture cache.
     */
    void loadTextures();

    /**
     * @brief Retrieves a texture from the cache based on an alias.
     * @param alias The alias of the tile texture.
     * @return A pointer to the SDL_Texture, or nullptr if not found.
     */
    SDL_Texture* getTexture(const std::string& alias) const;

    /**
     * @brief Cleans up and frees all loaded textures.
     */
    void cleanupTextures();
};

#endif // TILE_RENDERER_H
