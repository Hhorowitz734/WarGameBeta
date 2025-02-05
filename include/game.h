#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "RendererManager.h"
#include "TileMap.h"
#include "GlobalSettings.h"
#include <iostream>

class Game {
public:
    Game() : window(nullptr), rendererManager(nullptr), running(false) {
        
        // Get global settings
        const GlobalSettings& settings = GlobalSettings::getInstance();

        TILE_SIZE = settings.getTileSize();
        WINDOW_WIDTH = settings.getWindowWidth();
        WINDOW_HEIGHT = settings.getWindowHeight();
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
        rendererManager = new RendererManager(window);
        int numRows = WINDOW_HEIGHT / TILE_SIZE;
        int numCols = WINDOW_WIDTH / TILE_SIZE;
        tileMap.generateTiles(numRows, numCols, TILE_SIZE); 

        running = true;
        return true;
    }

    void run() {
        while (running) {
            processEvents();
            update();
            render();
        }
    }

    void cleanup() {
        delete rendererManager;
        if (window) SDL_DestroyWindow(window);
        SDL_Quit();
    }

private:
    bool running;
    SDL_Window* window;
    RendererManager* rendererManager;
    TileMap tileMap; // Owns all tiles

    int TILE_SIZE = 0;
    int WINDOW_WIDTH = 0;
    int WINDOW_HEIGHT = 0;

    void processEvents() {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                running = false;
            }
        }
    }

    void update() {
        // DO LATER
    }

    void render() {
        rendererManager->clear();
        rendererManager->getTileRenderer()->renderTiles(tileMap, TILE_SIZE); 
        rendererManager->present();
    }
};

#endif // GAME_H
