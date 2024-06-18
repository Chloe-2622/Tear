#include "ResourceManager.h"

std::map<std::string, sf::Texture, std::less<>> ResourceManager::textures;

std::unordered_map<std::string, sf::SoundBuffer> ResourceManager::buffers;
std::vector<sf::Sound> ResourceManager::sounds;

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

void ResourceManager::playSound(std::string const& soundPath) {

    if (buffers.find(soundPath) == buffers.end()) {
        // Load the sound buffer if it's not already loaded
        sf::SoundBuffer buffer;
        if (!buffer.loadFromFile(soundPath)) {
            std::cout << "Loading failed: " << soundPath << std::endl;
            return;
        }
        buffers[soundPath] = buffer;
    }

    sf::Sound sound(buffers[soundPath]);

    sounds.emplace_back(sound);
    sounds.back().play();
}