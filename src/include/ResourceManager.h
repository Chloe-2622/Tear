#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <string>
#include <map>
#include <unordered_map>

class ResourceManager {
    public:
        ResourceManager();
        static                                                      sf::Texture     getTexture(std::string const& texturePath);
        static                                                      void            playSound(std::string const& soundPath);
        static std::map<std::string, sf::Texture, std::less<>>      textures;
    
    private:
        static std::unordered_map<std::string, sf::SoundBuffer> buffers;
        static std::vector<sf::Sound> sounds;
};
