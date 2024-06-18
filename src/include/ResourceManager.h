#pragma once

#include <SFML/Graphics.hpp>
//#include <SFML/Audio.hpp>
#include <iostream>

class ResourceManager {
    public:
        ResourceManager();
        static                                                      sf::Texture getTexture(std::string const& texturePath);
        //static                                                      sf::SoundBuffer getSound(std::string const& soundPath);
        static std::map<std::string, sf::Texture, std::less<>>      textures;
        //static std::map<std::string, sf::SoundBuffer, std::less<>>  sounds;
};
