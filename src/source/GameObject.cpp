#include "GameObject.h"
#include <iostream>
#include <sstream>

using namespace std;

// Constructeurs
#pragma region Constructeurs
GameObject::GameObject(Transform const& transform, double speed, string const& texturePath, Faction faction):
    transform{ transform },
    texturePath{ texturePath },
    speed{ speed },
    faction{ faction }
{}

GameObject::GameObject(const pugi::xml_node& node, double speed, string const& texturePath, Faction faction) :
    texturePath{ texturePath },
    speed{ speed },
    faction{ faction }
{
    transform.position.x = node.attribute("x").as_double();
    transform.position.y = node.attribute("y").as_double();
    transform.size.x = node.attribute("size_x").as_double();
    transform.size.y = node.attribute("size_y").as_double();
    transform.rotation = 0;
}
#pragma endregion Constructeurs

// Render
void GameObject::Render(sf::RenderWindow &window) const {

    sf::Texture texture;
    texture = ResourceManager::getTexture(texturePath);

    sf::Sprite sprite;
    sprite.setTexture(texture);

    //cout << texture.getSize().x << ", " << texture.getSize().y;

    sprite.setScale(static_cast<float>(transform.size.x/texture.getSize().x) , static_cast<float>(transform.size.y / texture.getSize().y));
    sprite.setPosition(static_cast<float>(transform.position.x), static_cast<float>(transform.position.y));
    sprite.setRotation(static_cast<float>(transform.rotation));

    //Draw the sprite
    //cout << dump();
    window.draw(sprite);
}

// Update
std::unique_ptr<GameObject> GameObject::Update(double deltaTime, sf::View const& view, Vector2 windowSize, Vector2 playerPosition) {
    return nullptr; // Les objets qui n'ont pas d'update ou qui ne rajoutent pas de gameObjects retournent un pointeur null
}

// Out of View
double GameObject::exitViewValue() const { return 0; };

// Damages
#pragma region Damages
vector<unique_ptr<GameObject>>::const_iterator GameObject::hasHitSomething(const vector<unique_ptr<GameObject>>* gameObjects) const {

    auto it = gameObjects->begin();

    while (it != gameObjects->end()) {

        if (hasHitObject(**it)) {
            return it;
        }
        else {
            ++it;
        }
    }
    return it;
}













//void GameObject::hasHitSomething(std::vector<unique_ptr<GameObject>>* gameObjects) const {



    /*
    for (auto & gameObject : gameObjects) {
        if (hasHitObject(*gameObject)) {
            cout << "Coucou\n";
        }
    }
    
    //auto it = gameObjects.begin();

    
    for (auto const& gameObject : gameObjects) {
        if (hasHitObject(*gameObject)) {
            return gameObjects.end();
        }
    }

    return gameObjects.end();
    
    //auto it = gameObjects.end();

    
    while (it != gameObjects.end()) {
        //auto const& gameObject = *it;

        
        if (hasHitObject(*gameObject)) {
            return it;
        }
        else {
            ++it;
        }
    }
    //return it;*/
//}

bool GameObject::hasHitObject(GameObject const& gameObject) const {
    return gameObject.faction != this->faction && hasCollided(gameObject);
}
#pragma endregion Damages

// Setter
#pragma region Setter
void GameObject::setPosition(Vector2 position) { transform.position = position; };
void GameObject::move(Vector2 movement) { transform.position += movement; }
void GameObject::setTexturePath(string_view const& newTexturePath) { texturePath = newTexturePath; }
void GameObject::setSpeed(double newSpeed) { speed = newSpeed; }
void GameObject::setRotation(double newRotation) { transform.rotation = newRotation; }
#pragma endregion Setter

// Getter
#pragma region Getter
Vector2 GameObject::getPosition() const { return transform.position; }
Vector2 GameObject::getSize() const { return transform.size; }
double GameObject::getRotation() const { return transform.rotation; }
double GameObject::getSpeed() const { return speed; }
#pragma endregion Getter

// Debug
string GameObject::dump(string const& indent) const {
    ostringstream oss;
    oss << indent
        << "Position: x: " << transform.position.x << ", y: " << transform.position.y
        << "; Size: x: " << transform.size.x << ", y: " << transform.size.y
        << "; Rotation: " << transform.rotation << ", " << endl;
    return oss.str();
}