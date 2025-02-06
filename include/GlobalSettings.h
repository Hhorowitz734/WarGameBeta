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

    const std::string& getTileTexture(const std::string& tileType) const {
        return TILE_TEXTURES.at(tileType);
    }


    const std::unordered_map<std::string, std::string>& getTileTextures() const {
        return TILE_TEXTURES;
    }



private:

    const int WINDOW_WIDTH = 600;
    const int WINDOW_HEIGHT = 800;

    const int TILE_SIZE = 100;
    
    std::unordered_map<std::string, std::string> TILE_TEXTURES = {
        {"darkgrass", "../assets/darkgrass.png"},
        {"medgrass1", "../assets/medgrass_subtexture1.png"},
        {"medgrass2", "../assets/medgrass_subtexture2.png"},
        {"deadgrass1", "../assets/deadgrass1_subtexture1.png"},
        {"deadgrass2", "../assets/deadgrass1_subtexture2.png"},
        {"deadgrass3", "../assets/deadgrass1_subtexture3.png"},
    };

    GlobalSettings() {};


};


#endif