#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "GlobalSettings.h"
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <memory>

class TileMap {
public:

    TileMap();

    // Generates a grid of tiles with random textures
    void generateTiles(int numRows, int numCols, int tileSize, const std::vector<std::string>& textures);

    // Accessors
    const std::vector<std::shared_ptr<Tile>>& getTileMap() const;
    const std::shared_ptr<Tile> getTileAt(int x, int y) const;

    // Save + Load
    void saveToFile(const std::string& filename, const std::string& mapPathPrefix) const;
    void loadFromFile(const std::string& filename, const std::string& mapPathPrefix);

private:
    std::vector<std::shared_ptr<Tile>> tileMap;
    int numRows = 0;
    int numCols = 0;
    int TILE_SIZE = 0;
};

#endif // TILEMAP_H