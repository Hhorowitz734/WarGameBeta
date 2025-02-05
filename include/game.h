#ifndef GAME_H
#define GAME_H

#include <SDL.h>
#include "rendererManager.h"
#include "TileMap.h"

class Game {
public:
    Game() : window(nullptr), rendererManager(nullptr), running(false) {}

    ~Game() {
        cleanup();
    }

    bool init() {
        if (SDL_Init(SDL_INIT_VIDEO) < 0) {
            SDL_Log("SDL could not initialize! SDL Error: %s", SDL_GetError());
            return false;
        }

        window = SDL_CreateWindow("Tile Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 640, SDL_WINDOW_SHOWN);
        if (!window) {
            SDL_Log("Window could not be created! SDL Error: %s", SDL_GetError());
            return false;
        }

        rendererManager = new RendererManager(window);
        tileMap.generateTiles(10, 10); // Generates a 10x10 grid of tiles

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
        rendererManager->getTileRenderer()->renderTiles(tileMap); 
        rendererManager->present();
    }
};

#endif // GAME_H
