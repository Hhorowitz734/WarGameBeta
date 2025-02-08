#include "GlobalSettings.h"

// Singleton instance: Ensures only one instance of GlobalSettings exists.
GlobalSettings& GlobalSettings::getInstance() {
    static GlobalSettings instance;
    return instance;
}

// Constructor: Initializes default game settings.
GlobalSettings::GlobalSettings()
    : TILE_SIZE(100), WINDOW_WIDTH(1000), WINDOW_HEIGHT(600), MAP_PATH_PREFIX("../maps/"), playerId(1) {
    
    // Define tile textures with file paths.
    TILE_TEXTURES = {
        {"darkgrass", "../assets/darkgrass.png"},
        {"medgrass1", "../assets/medgrass_subtexture1.png"},
        {"medgrass2", "../assets/medgrass_subtexture2.png"},
        {"deadgrass1", "../assets/deadgrass1_subtexture1.png"},
        {"deadgrass2", "../assets/deadgrass1_subtexture2.png"},
        {"deadgrass3", "../assets/deadgrass1_subtexture3.png"},
    };
}

// Getters for game settings.
int GlobalSettings::getWindowWidth() const { 
    return WINDOW_WIDTH; 
}

int GlobalSettings::getWindowHeight() const { 
    return WINDOW_HEIGHT; 
}

int GlobalSettings::getTileSize() const { 
    return TILE_SIZE; 
}

const std::string& GlobalSettings::getMapPathPrefix() const { 
    return MAP_PATH_PREFIX; 
}

// Returns the map of tile textures.
const std::unordered_map<std::string, std::string>& GlobalSettings::getTileTextures() const {
    return TILE_TEXTURES;
}

// Returns the texture file path for a given tile type.
const std::string& GlobalSettings::getTileTexture(const std::string& tileType) const {
    return TILE_TEXTURES.at(tileType);
}

// Player ID management.
const int32_t& GlobalSettings::getPlayerId() const { 
    return playerId; 
}

// Checks if a given ID matches the player ID.
bool GlobalSettings::isPlayerId(const int32_t& id) const { 
    return playerId == id; 
}
