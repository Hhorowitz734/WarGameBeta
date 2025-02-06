#ifndef TILE_H
#define TILE_H

#include <string>

class Tile {
public:
    // Constructor
    Tile(int x, int y, const std::string& assetAlias, const int32_t ownerId);

    // Getters
    const std::string& getAssetAlias() const;
    int getX() const;
    int getY() const;

    const int32_t& getOwnerId() const;
private:
    std::string assetAlias;
    int x;
    int y;
    int32_t ownerId;
};

#endif // TILE_H
