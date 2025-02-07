#include "RendererManager.h"

// Constructor: Initializes the renderer and tile renderer.
RendererManager::RendererManager(SDL_Window* window, const std::unordered_map<std::string, std::string>& tileAssetMap, int tileSize)
    : TILE_SIZE(tileSize), currHover(-1, -1), hoverColor({255, 255, 0, 150}) {
    
    // Create the SDL renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        SDL_Log("Renderer could not be created! SDL Error: %s", SDL_GetError());
        return;
    }

    // Initialize the tile renderer
    tileRenderer = new TileRenderer(renderer, tileAssetMap);
}

// Destructor: Cleans up resources.
RendererManager::~RendererManager() {
    delete tileRenderer;
    SDL_DestroyRenderer(renderer);
}

// Clears the screen before rendering new frame.
void RendererManager::clear() {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
}

// Renders the tile map and highlights the hovered tile.
void RendererManager::render(const TileMap& tileMap) {
    // Render all tiles
    tileRenderer->renderTiles(tileMap, TILE_SIZE);

    // Draw hover highlight
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
    SDL_SetRenderDrawColor(renderer, hoverColor.r, hoverColor.g, hoverColor.b, hoverColor.a);
    SDL_Rect newRect = { 
        std::get<0>(currHover) * TILE_SIZE, 
        std::get<1>(currHover) * TILE_SIZE, 
        TILE_SIZE, TILE_SIZE 
    };
    SDL_RenderFillRect(renderer, &newRect);
}

// Presents the rendered content to the screen.
void RendererManager::present() {
    SDL_RenderPresent(renderer);
}

// Updates the hover tile position and highlight color.
void RendererManager::updateHover(int x, int y, SDL_Color newHoverColor) {
    currHover = std::make_tuple(x, y);
    hoverColor = newHoverColor;
}

// Accessor for the SDL renderer.
SDL_Renderer* RendererManager::getSDLRenderer() { 
    return renderer; 
}

// Accessor for the TileRenderer.
TileRenderer* RendererManager::getTileRenderer() { 
    return tileRenderer; 
}
