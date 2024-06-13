#include "GameObject.h"

GameObject::GameObject() {
    transform.position.x = 0;
    transform.position.y = 0;
    transform.size.x = 0;
    transform.size.y = 0;
    transform.rotation = 0;
    speed = 0;

    texturePath = "";
}

GameObject::GameObject(Transform transform, double speed) {
    this->transform = transform;
    this->speed = speed;

    texturePath = "";
}

void GameObject::Update(double deltaTime) {
}

void GameObject::Render(sf::RenderWindow &window) {
    sf::Texture texture;
    texture = ResourceManager::getTexture(texturePath);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(transform.position.x, transform.position.y);
    sprite.setRotation(transform.rotation);

    //Draw the sprite
    window.draw(sprite);
}