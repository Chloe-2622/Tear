#include "ResourceManager.h"

std::map<std::string, sf::Texture, std::less<>> ResourceManager::textures;

sf::Texture ResourceManager::getTexture(std::string const& texturePath) {

    if (textures.contains(texturePath)) {
        //std::cout << "Already loaded texture: " << texturePath << std::endl;
        return textures[texturePath];
    }

    else {
        std::cout << "Loading new texture: " << texturePath << std::endl;

        sf::Texture texture;
        if (!texture.loadFromFile(texturePath))
        {
            std::cout << "Loading failed: " << texturePath << std::endl;
            return texture;
        }
        textures[texturePath] = texture;

        return texture;
    }
}