#include "TileMap.h"
#include <iostream>

// Constructor: Initializes tile map settings from global configurations.
TileMap::TileMap() {
    numRows = GlobalSettings::getInstance().getTileSize();
    numCols = GlobalSettings::getInstance().getTileSize();
    TILE_SIZE = GlobalSettings::getInstance().getTileSize();
}

// Generates a grid of tiles with random textures.
void TileMap::generateTiles(int numRows, int numCols, int tileSize, const std::vector<std::string>& textures) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(0, textures.size() - 1);

    tileMap.clear();
    tileMap.reserve(numRows * numCols);

    for (int i = 0; i < numRows; i++) {
        for (int j = 0; j < numCols; j++) {
            tileMap.emplace_back(std::make_shared<Tile>(j * tileSize, i * tileSize, textures[dist(gen)], dist(gen)));
        }
    }
}

// Accessor: Returns the tile map.
const std::vector<std::shared_ptr<Tile>>& TileMap::getTileMap() const { 
    return tileMap; 
}

// Saves the current tile map to a binary file.
void TileMap::saveToFile(const std::string& filename, const std::string& mapPathPrefix) const {
    std::string fullPath = mapPathPrefix + filename;
    std::ofstream file(fullPath, std::ios::binary);

    if (!file) { 
        std::cerr << "Error: Failed to open file for saving: " << fullPath << std::endl;
        return; 
    }

    // Write map dimensions.
    file.write(reinterpret_cast<const char*>(&numRows), sizeof(numRows));
    file.write(reinterpret_cast<const char*>(&numCols), sizeof(numCols));

    // Store tiles.
    for (const auto& tile : tileMap) {
        int x = tile->getX();
        int y = tile->getY();
        int32_t ownerId = tile->getOwnerId();

        file.write(reinterpret_cast<const char*>(&x), sizeof(x));
        file.write(reinterpret_cast<const char*>(&y), sizeof(y));

        // Store asset alias.
        std::string alias = tile->getAssetAlias();
        size_t aliasLen = alias.size();
        file.write(reinterpret_cast<const char*>(&aliasLen), sizeof(aliasLen));
        file.write(alias.c_str(), aliasLen);

        // Store owner ID.
        file.write(reinterpret_cast<const char*>(&ownerId), sizeof(ownerId));
    }
}

// Loads a tile map from a binary file or generates a new one if the file is missing.
void TileMap::loadFromFile(const std::string& filename, const std::string& mapPathPrefix) {
    std::string fullPath = mapPathPrefix + filename;
    std::ifstream file(fullPath, std::ios::binary);

    if (!file) {
        std::cerr << "Warning: Map file not found: " << fullPath << ". Generating a new map.\n";

        // Generate and save a new map.
        generateTiles(numRows, numCols, TILE_SIZE, 
            {"medgrass2", "medgrass1", "darkgrass", "deadgrass1", "deadgrass2", "deadgrass3"});
        saveToFile(filename, mapPathPrefix);

        std::cerr << "New map saved to: " << fullPath << "\n";
        return;
    }

    // Read map dimensions.
    file.read(reinterpret_cast<char*>(&numRows), sizeof(numRows));
    file.read(reinterpret_cast<char*>(&numCols), sizeof(numCols));

    // Clear and allocate memory for tiles.
    tileMap.clear();
    tileMap.reserve(numRows * numCols);

    // Load tiles.
    for (int i = 0; i < numRows * numCols; i++) {
        int x, y;
        int32_t ownerId;

        file.read(reinterpret_cast<char*>(&x), sizeof(x));
        file.read(reinterpret_cast<char*>(&y), sizeof(y));

        // Read asset alias.
        size_t aliasLen;
        file.read(reinterpret_cast<char*>(&aliasLen), sizeof(aliasLen));
        std::string alias(aliasLen, '\0');
        file.read(&alias[0], aliasLen);

        // Read owner ID.
        file.read(reinterpret_cast<char*>(&ownerId), sizeof(ownerId));

        // Store tile.
        tileMap.emplace_back(std::make_shared<Tile>(x, y, alias, ownerId));
    }

    std::cout << "Successfully loaded map from: " << fullPath << "\n";
}

// Retrieves a tile at the given pixel coordinates.
const std::shared_ptr<Tile> TileMap::getTileAt(int x, int y) const {
    int tileX = x / TILE_SIZE;
    int tileY = y / TILE_SIZE;

    if (tileX >= 0 && tileX < numCols && tileY >= 0 && tileY < numRows) {
        int index = tileY * numCols + tileX; // Convert 2D coordinates to 1D index.
        return tileMap[index];
    }

    return nullptr; // Out of bounds.
}
