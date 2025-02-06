#include "GlobalSettings.h"

// Singleton instance
GlobalSettings& GlobalSettings::getInstance() {
    static GlobalSettings instance;
    return instance;
}

// Constructor
GlobalSettings::GlobalSettings()
    : TILE_SIZE(50), WINDOW_WIDTH(600), WINDOW_HEIGHT(800), MAP_PATH_PREFIX("../maps/") {
    TILE_TEXTURES = {
        {"darkgrass", "../assets/darkgrass.png"},
        {"medgrass1", "../assets/medgrass_subtexture1.png"},
        {"medgrass2", "../assets/medgrass_subtexture2.png"},
        {"deadgrass1", "../assets/deadgrass1_subtexture1.png"},
        {"deadgrass2", "../assets/deadgrass1_subtexture2.png"},
        {"deadgrass3", "../assets/deadgrass1_subtexture3.png"},
    };
}

// Getters
int GlobalSettings::getWindowWidth() const { return WINDOW_WIDTH; }
int GlobalSettings::getWindowHeight() const { return WINDOW_HEIGHT; }
int GlobalSettings::getTileSize() const { return TILE_SIZE; }
const std::string& GlobalSettings::getMapPathPrefix() const {return MAP_PATH_PREFIX; }

// Texture lookup
const std::unordered_map<std::string, std::string>& GlobalSettings::getTileTextures() const {
    return TILE_TEXTURES;
}

const std::string& GlobalSettings::getTileTexture(const std::string& tileType) const {
    return TILE_TEXTURES.at(tileType);
}
