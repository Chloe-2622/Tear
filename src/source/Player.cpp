#include "Player.h"
#include "Projectile_Basic.h"

using namespace std;

// Constructeur
Player::Player(Transform const& transform, double speed, string const& texturePath) : 
    GameObject{ transform, speed, texturePath, Faction::Ally } 
{}

// Render
void Player::Render(sf::RenderWindow& window) const {
    if (isRendered) {
        GameObject::Render(window);
    }
}

// Update
#pragma region Update
void Player::handleInput(sf::Keyboard::Key key, bool isPressed) {
    if (key == sf::Keyboard::Z) {
        isMovingUp = isPressed;
    }
    if (key == sf::Keyboard::S) {
        isMovingDown = isPressed;
    }
    if (key == sf::Keyboard::Q) {
        isMovingLeft = isPressed;
    }
    if (key == sf::Keyboard::D) {
        isMovingRight = isPressed;
    }
    if (key == sf::Keyboard::Space) {
        isShooting = isPressed;
    }
}

unique_ptr<GameObject> Player::Update(double deltaTime, sf::View const& view, Vector2 windowSize, Vector2 playerPosition) {
    Vector2 movement{ 0.f, 0.f };

    if (isMovingUp && getPosition().y > view.getCenter().y - windowSize.y/2) {
        movement.y -= getSpeed();
    }    
    if (isMovingDown && getPosition().y < view.getCenter().y + windowSize.y / 2 - getSize().y) {
        movement.y += getSpeed();
    }
    if (isMovingLeft && getPosition().x > 0) {
        movement.x -= getSpeed();
    }
    if (isMovingRight && getPosition().x < view.getCenter().x + windowSize.x / 2 - getSize().x) {
        movement.x += getSpeed();
    }
    move(movement);

    // Cooldowns
    if (invulnerabilityCooldown > 0.0) {
        invulnerabilityCooldown -= deltaTime;
        if (blinkCooldown > 0.0) {
            blinkCooldown -= deltaTime;
        }
        else {
            blinkCooldown = blinkTime;
            isRendered = !isRendered;
        }
    }
    else { isRendered = true; }
    if (shootingCooldown > 0.0) {
        shootingCooldown -= deltaTime;
    }

    if (isShooting && shootingCooldown <= 0.0) {
        cout << "Shooting" << endl;
        shootingCooldown = shootingTime;
        return shootProjectile();
    }
    return nullptr;
}

unique_ptr<Projectile> Player::shootProjectile() const {
    Vector2 projectileSize = { 32, 56 };

    cout << "Playze size : " << getSize().x << ", " << getSize().y << endl;

    Vector2 projectilePosition = { getPosition().x + getSize().x / 2 - projectileSize.x / 2, getPosition().y - projectileSize.y };
    Transform projectileTransform = { projectilePosition, projectileSize, 0 };
    string projectileTexturePath = "resources/Sprites/Basic_Projectile.png";

    return make_unique<Projectile_Basic>(projectileTransform, 20, projectileTexturePath, 10);
}

void Player ::followView(Vector2 movement) { move(movement); }
void Player::supressViewOffset(Vector2 offset) { move(offset); }
#pragma endregion Update

// Out of view
bool Player::isOutofView(sf::View const& view, Vector2 windowSize) const { return false; }

// Damages
#pragma region Damages
bool Player::hasCollided(GameObject const& gameObject) const { return false; } // The player cannot do damage by contact

bool Player::doDamage(GameObject& gameObject, double playerMultiplier) const { return false; } // Il ne fait vraiment pas de d�g�ts

bool Player::takeDamage(double damages) { // Par contre il en prend
    if (invulnerabilityCooldown <= 0) {
        healthPoints -= static_cast<int>(damages);
        invulnerabilityCooldown = invulnerabilityTime;
        return healthPoints <= 0;
    }
    else {
        cout << "Dont take damage\n";
    }
    return false;
}
#pragma endregion Damages

// Upgrades
void Player::upgrade(Upgrade upgrade) {}

// Getter
double Player::getDamageMultiplier() const { return damageMultiplier; }


