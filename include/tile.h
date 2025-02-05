#ifndef TILE_H
#define TILE_H

#include <string>

class Tile {

public:

    Tile(int x, int y, const std::string& path)
        : x(x), y(y), assetPath(path) {}

    // Getters and setters
    const std::string& getAssetPath() const { return assetPath; }

    int getX() const { return x; }
    int getY() const { return y; }


    
private:
    std::string assetPath = "../assets/darkgrass.png";
    int x, y = 0;
    
};

#endif