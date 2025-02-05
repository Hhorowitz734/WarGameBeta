#ifndef TILEMAP_H
#define TILEMAP_H

#include "tile.h"
#include <vector>

class TileMap {
public:
    
    void generateTiles(int numRows, int numCols) {
        /**
         * Generate numRows * numCols tiles
         */
        std::vector<Tile> row; 
        for (int i = 0; i < numRows; i++) {
            row = {}; 
            for (int j = 0; j < numCols; j++) {
                Tile newTile = Tile(i * 64, j * 64, "../assets/darkgrass.png");
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