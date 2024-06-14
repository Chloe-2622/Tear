#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class ResourceManager {
    public:
        ResourceManager();
        static sf::Texture getTexture(std::string texturePath);
        static std::map<std::string, sf::Texture> textures;
};