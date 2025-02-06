#ifndef GLOBAL_SETTINGS_H
#define GLOBAL_SETTINGS_H

#include <unordered_map>
#include <string>
#include <iostream>

class GlobalSettings {
public:

    // Singleton
    GlobalSettings(const GlobalSettings&) = delete;
    GlobalSettings& operator=(const GlobalSettings&) = delete;
    static GlobalSettings& getInstance();

    // Getters
    int getWindowWidth() const;
    int getWindowHeight() const;
    int getTileSize() const;
    const std::unordered_map<std::string, std::string>& getTileTextures() const;
    const std::string& getTileTexture(const std::string& tileType) const;
    const std::string& getMapPathPrefix() const;
    const int32_t& getPlayerId() const;
    bool isPlayerId(const int32_t& id) const;
private:

    GlobalSettings(); 

    // Config
    const int WINDOW_WIDTH;
    const int WINDOW_HEIGHT;
    const int TILE_SIZE;

    const std::string MAP_PATH_PREFIX;

    // Textures
    std::unordered_map<std::string, std::string> TILE_TEXTURES;

    // User Settings
    const int32_t playerId;

};

#endif // GLOBAL_SETTINGS_H
