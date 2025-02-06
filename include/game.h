#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "RendererManager.h"
#include "TileMap.h"
#include "GlobalSettings.h"
#include "CursorManager.h"

#include <iostream>
#include <memory>

class Game {
public:
    Game() 
        : window(nullptr), 
        rendererManager(nullptr), 
        running(false), 
        cursorManager(GlobalSettings::getInstance().getTileSize()) // ✅ Initialize in list
    {
        // Get global settings
        const GlobalSettings& settings = GlobalSettings::getInstance();
        TILE_SIZE = settings.getTileSize();
        WINDOW_WIDTH = settings.getWindowWidth();
        WINDOW_HEIGHT = settings.getWindowHeight();
        TILE_TEXTURES = settings.getTileTextures();
    }


    ~Game() {
        cleanup();
    }

    bool init() {

        // Initialize window
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            SDL_Log("SDL could not initialize! SDL Error: %s", SDL_GetError());
            return false;
        }

        window = SDL_CreateWindow(
            "Tile Game", 
            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
            WINDOW_WIDTH, 
            WINDOW_HEIGHT, 
            SDL_WINDOW_SHOWN);

        if (!window) {
            SDL_Log("Window could not be created! SDL Error: %s", SDL_GetError());
            return false;
        }

        // Initialize RenderManager
        rendererManager = std::make_unique<RendererManager>(window, TILE_TEXTURES, TILE_SIZE);
        int numRows = WINDOW_HEIGHT / TILE_SIZE;
        int numCols = WINDOW_WIDTH / TILE_SIZE;
        tileMap.generateTiles(numRows, numCols, TILE_SIZE, {"medgrass2", "medgrass1", "darkgrass", "deadgrass1", "deadgrass2", "deadgrass3"}); 

        running = true;
        return true;
    }

    void run() {
        while (running) {
            update();
            render();
            processEvents();
        }
    }

    void cleanup() {
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
    }

private:
    bool running;
    SDL_Window* window;
    std::unique_ptr<RendererManager> rendererManager;
    TileMap tileMap; // Owns all tiles

    CursorManager cursorManager;

    int TILE_SIZE = 0;
    int WINDOW_WIDTH = 0;
    int WINDOW_HEIGHT = 0;

    std::unordered_map<std::string, std::string> TILE_TEXTURES = {};

    void processEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
            if (event.type == SDL_MOUSEMOTION) {
                int hoverX, hoverY;
                if (cursorManager.update(event, WINDOW_WIDTH / TILE_SIZE, WINDOW_HEIGHT / TILE_SIZE, hoverX, hoverY)) {
                    rendererManager->updateHover(hoverX, hoverY); // Send coordinates directly
                }

            }
        }
    }

    void update() {
        // DO LATER
    }

    void render() {
        rendererManager->clear();
        rendererManager->render(tileMap); 
        rendererManager->present();
    }
};

#endif // GAME_H
