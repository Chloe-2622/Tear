#include <iostream>
#include <sstream>
#include "GameObjects/GameObject.h"

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
#pragma region Update
void GameObject::Update(double deltaTime, sf::View const& view, Vector2 windowSize, Vector2 playerPosition,
    std::vector<std::unique_ptr<GameObject>>* gameObjects,
    LevelUpdateValues* levelUpdateValues) {

    if (isOutRenderZone(view, windowSize)) {
        exitRenderZone(levelUpdateValues);
    }
}

void GameObject::followView(Vector2 viewMovement) {
    if (followingView) { move(viewMovement); }
}

void GameObject::move(Vector2 movement) { transform.position += movement; }
#pragma endregion Update

// Out of View
void GameObject::exitRenderZone(LevelUpdateValues* levelUpdateValues) {
    levelUpdateValues->killedObjects.push_back(this);
}

// Damages
#pragma region Collision
void GameObject::handleCollisions(const std::vector<std::unique_ptr<GameObject>>* gameObjects, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) {
    for (auto const& gameObject : *gameObjects) {
        handleCollision(*gameObject, playerModifiersValue, levelUpdateValues);
    }
}

void GameObject::handleCollision(GameObject& gameObject, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) {
    if (*this != gameObject && ((gameObject.faction != this->faction || friendlyFire) && hasCollided(gameObject))) {
        onCollissionReaction(gameObject, playerModifiersValue, levelUpdateValues);
    }
}

bool GameObject::hasCollided(GameObject const& gameObject) const {
    // Box collisions
    // Same line on X
    if (gameObject.getPosition().x < getPosition().x + getSize().x && gameObject.getPosition().x + gameObject.getSize().x > getPosition().x) {

        // Same column on Y 
        return gameObject.getPosition().y < getPosition().y + getSize().y && gameObject.getPosition().y + gameObject.getSize().y > getPosition().y;
    }
    return false;
}

void GameObject::onCollissionReaction(GameObject& gameObject, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) {
    if (onCollissionAction(gameObject, playerModifiersValue, levelUpdateValues) && destroyOnHit) {
        levelUpdateValues->killedObjects.push_back(this);
    }
}
#pragma endregion Collision

// Setter
#pragma region Setter
void GameObject::setPosition(Vector2 position) { transform.position = position; };
void GameObject::setTexturePath(string_view const& newTexturePath) { texturePath = newTexturePath; }
void GameObject::setSpeed(double newSpeed) { speed = newSpeed; }
void GameObject::setRotation(double newRotation) { transform.rotation = newRotation; }

// Booléen
void GameObject::setFriendlyFire(bool newFriendlyFire) { friendlyFire = newFriendlyFire; }
void GameObject::setFollowingView(bool newFollowingView) { followingView = newFollowingView; }
void GameObject::setDestroyOnHit(bool newDestroyOnHit) { destroyOnHit = newDestroyOnHit; }
#pragma endregion Setter

// Getter
#pragma region Getter
Vector2 GameObject::getPosition() const { return transform.position; }
Vector2 GameObject::getSize() const { return transform.size; }
double GameObject::getRotation() const { return transform.rotation; }
double GameObject::getSpeed() const { return speed; }
#pragma endregion Getter

// Operations
bool GameObject::operator==(const GameObject& g) const
{
    return transform == g.transform;
}

// Debug
string GameObject::dump(string const& indent) const {
    ostringstream oss;
    oss << indent
        << "Position: x: " << transform.position.x << ", y: " << transform.position.y
        << "; Size: x: " << transform.size.x << ", y: " << transform.size.y
        << "; Rotation: " << transform.rotation << ", " << endl;
    return oss.str();
}