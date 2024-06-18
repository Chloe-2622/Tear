#include "Goal.h"

Goal::Goal(Transform const& transform, std::string const& texturePath) :
	transform{ transform },
	texturePath{ texturePath }
{}

bool Goal::isReached(Player const& player) const {
    // Same line on X
    if (player.getPosition().x < transform.position.x + transform.size.x && player.getPosition().x + player.getSize().x > transform.position.x) {

        // Same column on Y 
        return player.getPosition().y < transform.position.y + transform.size.y && player.getPosition().y + player.getSize().y > transform.position.y;
    }
    return false;
}

void Goal::Render(sf::RenderWindow& window) const {
    sf::Texture texture;
    texture = ResourceManager::getTexture(texturePath);

    sf::Sprite sprite;
    sprite.setTexture(texture);

    sprite.setScale(static_cast<float>(transform.size.x / texture.getSize().x), static_cast<float>(transform.size.y / texture.getSize().y));
    sprite.setPosition(static_cast<float>(transform.position.x), static_cast<float>(transform.position.y));
    sprite.setRotation(static_cast<float>(transform.rotation));

    //Draw the sprite
    window.draw(sprite);
}
