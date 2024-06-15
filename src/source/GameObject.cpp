#include "GameObject.h"
#include <iostream>
#include <sstream>

#pragma region Constructeurs
GameObject::GameObject() {
    transform.position.x = 0;
    transform.position.y = 0;
    transform.size.x = 0;
    transform.size.y = 0;
    transform.rotation = 0;
    speed = 0;

    texturePath = "";
}

GameObject::GameObject(Transform transform, double speed, std::string texturePath):
    transform{ transform },
    speed{ speed },
    texturePath{ texturePath }
{}


GameObject::GameObject(GameObject const& gameObject) :
    transform{ gameObject.transform },
    speed{ gameObject.speed },
    texturePath{ gameObject.texturePath }
{}
#pragma endregion Constructeurs


void GameObject::Update(double deltaTime) {
}

void GameObject::Render(sf::RenderWindow &window) const {
    sf::Texture texture;
    texture = ResourceManager::getTexture(texturePath);

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(static_cast<float>(transform.position.x), static_cast<float>(transform.position.y));
    sprite.setRotation(static_cast<float>(transform.rotation));

    //Draw the sprite
    //std::cout << dump();
    window.draw(sprite);
}

Vector2 GameObject::getPosition() const { return transform.position; }
Vector2 GameObject::getSize() const { return transform.size; }
double GameObject::getRotation() const { return transform.rotation; }

void GameObject::move(Vector2 movement) {
    transform.position.x += movement.x;
    transform.position.y += movement.y;
}

std::string GameObject::dump(std::string const& indent) const {
    std::ostringstream oss;
    oss << indent
        << "Position: x: " << transform.position.x << ", y: " << transform.position.y
        << "; Size: x: " << transform.size.x << ", y: " << transform.size.y
        << "; Rotation: " << transform.rotation << ", " << std::endl;
    return oss.str();
}

double GameObject::exitView() const {
    return 0;
}
