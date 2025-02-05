#include "game.h"

int main(int argc, char* argv[]) {
    Game game;

    if (!game.init()) {
        return 1; // Exit if initialization fails
    }

    game.run();
    
    return 0;
}
