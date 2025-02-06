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


// Save + Load
void TileMap::saveToFile(const std::string& filename, const std::string& mapPathPrefix) const {
    
    // initialize fstream
    std::string fullPath = mapPathPrefix + filename;
    std::ofstream file(fullPath, std::ios::binary);
    if (!file) { return; }

    // Write num rows and num cols to top of file
    file.write(reinterpret_cast<const char*>(&numRows), sizeof(numRows));
    file.write(reinterpret_cast<const char*>(&numCols), sizeof(numCols));

    // Store tiles
    for (const auto& tile : tileMap) {

        int x = tile.getX();
        int y = tile.getY();

        file.write(reinterpret_cast<const char*>(&x), sizeof(x));
        file.write(reinterpret_cast<const char*>(&y), sizeof(y));

        // Store asset "alias"
        std::string alias = tile.getAssetAlias();
        size_t aliasLen = alias.size();
        file.write(reinterpret_cast<const char*>(&aliasLen), sizeof(aliasLen));
        file.write(alias.c_str(), aliasLen);

    }
}

void TileMap::loadFromFile(const std::string& filename, const std::string& mapPathPrefix) {
    
    // initialize fstream
    std::string fullPath = mapPathPrefix + filename;
    std::ifstream file(fullPath, std::ios::binary);
    if (!file) { return; }

    // Read num rows and num cols from top of file
    file.read(reinterpret_cast<char*>(&numRows), sizeof(numRows));
    file.read(reinterpret_cast<char*>(&numCols), sizeof(numCols));

    // Clear and allocate memory for tiles
    tileMap.clear();
    tileMap.reserve(numRows * numCols);

    // Load tiles
    for (int i = 0; i < numRows * numCols; i++) {

        int x, y;

        file.read(reinterpret_cast<char*>(&x), sizeof(x));
        file.read(reinterpret_cast<char*>(&y), sizeof(y));

        // Read asset "alias"
        size_t aliasLen;
        file.read(reinterpret_cast<char*>(&aliasLen), sizeof(aliasLen));
        std::string alias(aliasLen, '\0');
        file.read(&alias[0], aliasLen);

        // Store tile
        tileMap.emplace_back(x, y, alias);
    }
}
