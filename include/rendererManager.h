#ifndef RENDERER_MANAGER_H
#define RENDERER_MANAGER_H

#include <SDL.h>
#include <unordered_map>
#include <tuple>
#include "TileRenderer.h"
#include "TileMap.h"

/**
 * @class RendererManager
 * @brief Handles rendering operations, including drawing the tile map and hover effects.
 */
class RendererManager {
public:
    /**
     * @brief Constructs a RendererManager and initializes the SDL renderer.
     * @param window The SDL window where rendering occurs.
     * @param tileAssetMap A map of tile types to their corresponding texture file paths.
     * @param tileSize The size of each tile in pixels.
     */
    RendererManager(SDL_Window* window, const std::unordered_map<std::string, std::string>& tileAssetMap, int tileSize);

    /**
     * @brief Destructor that cleans up the renderer and related resources.
     */
    ~RendererManager();

    /**
     * @brief Clears the screen before rendering a new frame.
     */
    void clear();

    /**
     * @brief Renders the tile map and the highlighted hover tile.
     * @param tileMap The tile map to be rendered.
     */
    void render(const TileMap& tileMap);

    /**
     * @brief Presents the rendered content to the screen.
     */
    void present();

    /**
     * @brief Updates the hover position and changes the highlight color.
     * @param x The x-coordinate of the hovered tile.
     * @param y The y-coordinate of the hovered tile.
     * @param newHoverColor The new color for the hover highlight.
     */
    void updateHover(int x, int y, SDL_Color newHoverColor);

    /**
     * @brief Gets the SDL renderer.
     * @return A pointer to the SDL_Renderer instance.
     */
    SDL_Renderer* getSDLRenderer();

    /**
     * @brief Gets the TileRenderer responsible for rendering individual tiles.
     * @return A pointer to the TileRenderer instance.
     */
    TileRenderer* getTileRenderer();

private:
    SDL_Renderer* renderer;  ///< SDL renderer for rendering content.
    TileRenderer* tileRenderer; ///< Tile renderer for managing tile textures.
    const int TILE_SIZE; ///< Size of each tile in pixels.

    std::tuple<int, int> currHover; ///< Stores the current hover tile coordinates.
    SDL_Color hoverColor; ///< Color used to highlight hovered tiles.
};

#endif // RENDERER_MANAGER_H
