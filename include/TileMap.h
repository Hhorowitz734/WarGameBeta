#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include <vector>

class TileMap {
public:
    
    void generateTiles(int numRows, int numCols, int tileSize) {
        /**
         * Generate numRows * numCols tiles
         */
        std::vector<Tile> row; 
        for (int i = 0; i < numRows; i++) {
            row = {}; 
            for (int j = 0; j < numCols; j++) {
                Tile newTile = Tile(j * tileSize, i * tileSize, "../assets/darkgrass.png");
                row.push_back(newTile);
            }
            tileMap.push_back(row);
        }

    }

    const std::vector<std::vector<Tile>>& getTileMap() const { return tileMap; }



private:

    std::vector<std::vector<Tile>> tileMap;

};




#endif