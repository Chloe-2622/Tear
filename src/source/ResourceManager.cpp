#include "ResourceManager.h"

std::map<std::string, sf::Texture> ResourceManager::textures;

sf::Texture ResourceManager::getTexture(std::string texturePath) {
    std::cout << "Loading texture: " << texturePath << std::endl;

    return textures[texturePath];
}