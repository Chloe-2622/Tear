#include "GameObject.h"
#include <iostream>
#include <sstream>

#pragma region Constructeurs
GameObject::GameObject() :
    speed{ 0 },
    texturePath{ "" }
{
    transform.position.x = 0;
    transform.position.y = 0;
    transform.size.x = 0;
    transform.size.y = 0;
    transform.rotation = 0;
}

GameObject::GameObject(Transform const& transform, double speed, std::string const& texturePath):
    transform{ transform },
    speed{ speed },
    texturePath{ texturePath }
{}

GameObject::GameObject(const pugi::xml_node& node, double speed, std::string texturePath) :
    speed{ speed },
    texturePath{ texturePath }
{
    transform.position.x = node.attribute("x").as_double();
    transform.position.y = node.attribute("y").as_double();
    transform.size.x = node.attribute("size_x").as_double();
    transform.size.y = node.attribute("size_y").as_double();
    transform.rotation = 0;
}


GameObject::GameObject(GameObject const& gameObject) :
    transform{ gameObject.transform },
    speed{ gameObject.speed },
    texturePath{ gameObject.texturePath }
{}
#pragma endregion Constructeurs

// Render
void GameObject::Update(double deltaTime, double scrollingSpeed, float viewPositionY, float windowLenght, Vector2 playerPosition) {}
void GameObject::Render(sf::RenderWindow &window) const {

    sf::Texture texture;
    texture = ResourceManager::getTexture(texturePath);

    sf::Sprite sprite;
    sprite.setTexture(texture);

    //std::cout << texture.getSize().x << ", " << texture.getSize().y;

    sprite.setScale(static_cast<float>(transform.size.x/texture.getSize().x) , static_cast<float>(transform.size.y / texture.getSize().y));
    sprite.setPosition(static_cast<float>(transform.position.x), static_cast<float>(transform.position.y));
    sprite.setRotation(static_cast<float>(transform.rotation));

    //Draw the sprite
    //std::cout << dump();
    window.draw(sprite);
}

void GameObject::move(Vector2 movement) {
    transform.position.x += movement.x;
    transform.position.y += movement.y;
}

#pragma region Override if necessary
bool GameObject::isOutofView(sf::FloatRect currentViewBox) const { return false; }
double GameObject::exitView() const { return 0; }
//void GameObject::doDamage(GameObject gameObject, double playerMultiplier) const {/*Method to override*/}
bool GameObject::takeDamage(double damages) { return false; }
#pragma endregion Override if necessary




#pragma region Getter
Vector2 GameObject::getPosition() const { return transform.position; }
Vector2 GameObject::getSize() const { return transform.size; }
double GameObject::getRotation() const { return transform.rotation; }
double GameObject::getSpeed() const { return speed; }
#pragma endregion Getter

// Debug
std::string GameObject::dump(std::string const& indent) const {
    std::ostringstream oss;
    oss << indent
        << "Position: x: " << transform.position.x << ", y: " << transform.position.y
        << "; Size: x: " << transform.size.x << ", y: " << transform.size.y
        << "; Rotation: " << transform.rotation << ", " << std::endl;
    return oss.str();
}