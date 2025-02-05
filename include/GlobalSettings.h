#ifndef GLOBAL_SETTINGS_H
#define GLOBAL_SETTINGS_H

#include <unordered_map>

class GlobalSettings {

public:
    GlobalSettings(const GlobalSettings&) = delete; //Singleton for obvious reasons
    GlobalSettings& operator=(const GlobalSettings&) = delete;


    // Access point
    static GlobalSettings& getInstance() {
        static GlobalSettings instance;
        return instance;
    }

    int getWindowWidth() const { return WINDOW_WIDTH; }
    int getWindowHeight() const { return WINDOW_HEIGHT; }
    
    int getTileSize() const { return TILE_SIZE; }

    std::string getTileTexture(const std::string& tileType) const {
        auto it = TILE_TEXTURES.find(tileType);
        return (it != TILE_TEXTURES.end()) ? it->second : "";
    }



private:

    const int WINDOW_WIDTH = 600;
    const int WINDOW_HEIGHT = 800;

    const int TILE_SIZE = 100;
    
    std::unordered_map<std::string, std::string> TILE_TEXTURES = {
        {"darkgrass", "../assets/darkgrass.png"}
    };

    GlobalSettings() {};


};


#endif