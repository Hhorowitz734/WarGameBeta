#ifndef TILE_H
#define TILE_H

#include <string>

/**
 * @class Tile
 * @brief Represents a tile in the game world with position, asset type, and ownership data.
 */
class Tile {
public:
    /**
     * @brief Constructs a Tile with given coordinates, asset alias, and owner ID.
     * @param x The x-coordinate of the tile.
     * @param y The y-coordinate of the tile.
     * @param assetAlias The alias representing the tile's visual asset.
     * @param ownerId The ID of the player who owns this tile.
     */
    Tile(int x, int y, const std::string& assetAlias, const int32_t ownerId);

    /**
     * @brief Gets the alias of the tile's asset.
     * @return A reference to the asset alias string.
     */
    const std::string& getAssetAlias() const;

    /**
     * @brief Gets the x-coordinate of the tile.
     * @return The x-coordinate.
     */
    int getX() const;

    /**
     * @brief Gets the y-coordinate of the tile.
     * @return The y-coordinate.
     */
    int getY() const;

    /**
     * @brief Gets the ID of the tile's owner.
     * @return A reference to the owner's ID.
     */
    const int32_t& getOwnerId() const;

private:
    std::string assetAlias; ///< The alias representing the tile's visual asset.
    int x; ///< The x-coordinate of the tile.
    int y; ///< The y-coordinate of the tile.
    int32_t ownerId; ///< The ID of the player who owns the tile.
};

#endif // TILE_H
