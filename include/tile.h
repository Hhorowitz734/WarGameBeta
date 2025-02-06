#ifndef TILE_H
#define TILE_H

#include <string>

class Tile {
public:
    // Constructor
    Tile(int x, int y, const std::string& assetAlias);

    // Getters
    const std::string& getAssetAlias() const;
    int getX() const;
    int getY() const;

private:
    std::string assetAlias;
    int x;
    int y;
};

#endif // TILE_H
