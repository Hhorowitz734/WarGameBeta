#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include <vector>
#include <string>
#include <random>

class TileMap {
public:
    // Generates a grid of tiles with random textures
    void generateTiles(int numRows, int numCols, int tileSize, const std::vector<std::string>& textures);

    // Accessors
    const std::vector<Tile>& getTileMap() const;

private:
    std::vector<Tile> tileMap;
    int numRows = 0;
    int numCols = 0;
};

#endif // TILEMAP_H