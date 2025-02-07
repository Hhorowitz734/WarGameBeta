#include "Tile.h"

// Constructor: Initializes a tile with position, asset alias, and owner ID.
Tile::Tile(int x, int y, const std::string& assetAlias, const int32_t ownerId)
    : x(x), y(y), assetAlias(assetAlias), ownerId(ownerId) {}

// Getters for tile properties.
const std::string& Tile::getAssetAlias() const { 
    return assetAlias; 
}

int Tile::getX() const { 
    return x; 
}

int Tile::getY() const { 
    return y; 
}

const int32_t& Tile::getOwnerId() const { 
    return ownerId; 
}
