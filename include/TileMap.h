#ifndef TILEMAP_H
#define TILEMAP_H

#include "Tile.h"
#include "GlobalSettings.h"
#include <vector>
#include <string>
#include <random>
#include <fstream>
#include <memory>

/**
 * @class TileMap
 * @brief Manages a grid of tiles, including generation, retrieval, saving, and loading.
 */
class TileMap {
public:
    /**
     * @brief Constructs a TileMap and initializes settings from global configurations.
     */
    TileMap();

    /**
     * @brief Generates a grid of tiles with random textures.
     * @param numRows The number of rows in the tile grid.
     * @param numCols The number of columns in the tile grid.
     * @param tileSize The size of each tile in pixels.
     * @param textures A list of texture aliases used for tile generation.
     */
    void generateTiles(int numRows, int numCols, int tileSize, const std::vector<std::string>& textures, bool isInner = false);

    /**
     * @brief Gets the list of all tiles in the map.
     * @return A constant reference to the vector of shared tile pointers.
     */
    const std::vector<std::shared_ptr<Tile>>& getTileMap() const;

    /**
     * @brief Retrieves a tile at specific pixel coordinates.
     * @param x The x-coordinate in pixels.
     * @param y The y-coordinate in pixels.
     * @return A shared pointer to the tile at the given coordinates, or nullptr if out of bounds.
     */
    const std::shared_ptr<Tile> getTileAt(int x, int y) const;

    /**
     * @brief Saves the tile map to a binary file.
     * @param filename The name of the file to save to.
     * @param mapPathPrefix The path prefix where the file should be saved.
     */
    void saveToFile(const std::string& filename, const std::string& mapPathPrefix) const;

    /**
     * @brief Loads a tile map from a binary file. If the file is missing, generates a new map.
     * @param filename The name of the file to load from.
     * @param mapPathPrefix The path prefix where the file is located.
     */
    void loadFromFile(const std::string& filename, const std::string& mapPathPrefix);

private:
    std::vector<std::shared_ptr<Tile>> tileMap; ///< Stores the tile objects in the map.
    int numRows = 0; ///< Number of rows in the tile grid.
    int numCols = 0; ///< Number of columns in the tile grid.
    int TILE_SIZE = 0; ///< Size of each tile in pixels.
};

#endif // TILEMAP_H
