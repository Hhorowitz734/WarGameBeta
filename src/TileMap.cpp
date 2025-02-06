#include "TileMap.h"

// Generates a grid of tiles with random textures
void TileMap::generateTiles(int numRows, int numCols, int tileSize, const std::vector<std::string>& textures) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, textures.size() - 1);

    this->numRows = numRows;
    this->numCols = numCols;

    tileMap.clear();
    tileMap.reserve(numRows * numCols);

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            tileMap.emplace_back(j * tileSize, i * tileSize, textures[dist(gen)]);
        }
    }
}

// Accessor for the tile map
const std::vector<Tile>& TileMap::getTileMap() const { 
    return tileMap; 
}
