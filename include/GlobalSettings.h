#ifndef GLOBAL_SETTINGS_H
#define GLOBAL_SETTINGS_H

#include <unordered_map>
#include <string>

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
private:

    GlobalSettings(); 

    // Config
    const int WINDOW_WIDTH;
    const int WINDOW_HEIGHT;
    const int TILE_SIZE;

    const std::string MAP_PATH_PREFIX;

    // Textures
    std::unordered_map<std::string, std::string> TILE_TEXTURES;

};

#endif // GLOBAL_SETTINGS_H
