#include "Tile.h"

// Constructor
Tile::Tile(int x, int y, const std::string& assetAlias)
    : x(x), y(y), assetAlias(assetAlias) {}

// Getters
const std::string& Tile::getAssetAlias() const { return assetAlias; }
int Tile::getX() const { return x; }
int Tile::getY() const { return y; }
