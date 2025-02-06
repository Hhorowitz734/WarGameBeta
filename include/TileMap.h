#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include <vector>
#include <string>
#include <random>


class TileMap {
public:
    
    void generateTiles(int numRows, int numCols, int tileSize, std::vector<std::string> textures) {
        /**
         * Generate numRows * numCols tiles
         */

        // RANDOMNESS
        std::random_device rd; 
        std::mt19937 gen(rd());  
        std::uniform_int_distribution<int> dist(0, textures.size() - 1); 
        int randomIndex;

        // Save num rows and cols
        numRows = numRows;
        numCols = numCols;

        // Memory
        tileMap.clear();
        tileMap.reserve(numRows * numCols); // Preallocate storage


        // GRID GENERATION
        std::vector<Tile> row; 
        for (int i = 0; i < numRows; i++) {
            for (int j = 0; j < numCols; j++) {
                randomIndex = dist(gen);
                tileMap.emplace_back(j * tileSize, i * tileSize, textures[randomIndex]);
            }
        }

    }

    const std::vector<Tile>& getTileMap() const { return tileMap; }



private:

    std::vector<Tile> tileMap;
    int numRows, numCols = 0;

};




#endif