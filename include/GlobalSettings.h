#ifndef GLOBAL_SETTINGS_H
#define GLOBAL_SETTINGS_H

#include <unordered_map>
#include <string>
#include <iostream>

/**
 * @class GlobalSettings
 * @brief Singleton class that manages global game settings and configurations.
 */
class GlobalSettings {
public:
    /**
     * @brief Deleted copy constructor to prevent copying.
     */
    GlobalSettings(const GlobalSettings&) = delete;

    /**
     * @brief Deleted assignment operator to enforce singleton pattern.
     */
    GlobalSettings& operator=(const GlobalSettings&) = delete;

    /**
     * @brief Provides access to the singleton instance of GlobalSettings.
     * @return Reference to the singleton instance.
     */
    static GlobalSettings& getInstance();

    /**
     * @brief Gets the width of the game window.
     * @return The window width in pixels.
     */
    int getWindowWidth() const;

    /**
     * @brief Gets the height of the game window.
     * @return The window height in pixels.
     */
    int getWindowHeight() const;

    /**
     * @brief Gets the size of each tile in pixels.
     * @return The tile size.
     */
    int getTileSize() const;

    /**
     * @brief Retrieves the map of tile textures.
     * @return A reference to the unordered map of tile texture file paths.
     */
    const std::unordered_map<std::string, std::string>& getTileTextures() const;

    /**
     * @brief Gets the file path for a specific tile texture.
     * @param tileType The tile type identifier.
     * @return The file path of the corresponding texture.
     */
    const std::string& getTileTexture(const std::string& tileType) const;

    /**
     * @brief Gets the map file path prefix.
     * @return The map path prefix as a string.
     */
    const std::string& getMapPathPrefix() const;

    /**
     * @brief Gets the player's unique ID.
     * @return The player ID.
     */
    const int32_t& getPlayerId() const;

    /**
     * @brief Checks if a given ID matches the player ID.
     * @param id The ID to check.
     * @return True if the given ID matches the player's ID, false otherwise.
     */
    bool isPlayerId(const int32_t& id) const;

private:
    /**
     * @brief Private constructor to enforce the singleton pattern.
     */
    GlobalSettings();

    // Game configuration
    const int WINDOW_WIDTH;  ///< Width of the game window.
    const int WINDOW_HEIGHT; ///< Height of the game window.
    const int TILE_SIZE;     ///< Size of each tile in pixels.

    const std::string MAP_PATH_PREFIX; ///< Path prefix for storing map files.

    // Texture management
    std::unordered_map<std::string, std::string> TILE_TEXTURES; ///< Stores tile texture file paths.

    // User settings
    const int32_t playerId; ///< The player's unique identifier.
};

#endif // GLOBAL_SETTINGS_H
