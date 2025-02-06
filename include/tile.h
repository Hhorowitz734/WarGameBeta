#ifndef TILE_H
#define TILE_H

#include <string>

class Tile {

public:

    Tile(int x, int y, const std::string& assetAlias)
        : x(x), y(y), assetAlias(assetAlias) {}

    // Getters and setters
    const std::string& getAssetAlias() const { return assetAlias; }

    int getX() const { return x; }
    int getY() const { return y; }


    
private:
    std::string assetAlias = "darkgrass";
    int x, y = 0;
    
};

#endif