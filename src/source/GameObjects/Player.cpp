#include "GameObjects/Player.h"

using namespace std;

void Player::setParams() {
    healthPoints = 100;
    damageMultiplier = 1.0;

    goldCount = 0;
    goldMultiplier = 1.0;

    projectileDuplication = 1.0;

    // GameObject
    setSpeed(250);
    setTexturePath("resources/Sprites/Tetine.png");

    // Booleans
    setFriendlyFire(false);
    setFollowingView(true);
    setDestroyOnHit(false);
}

// Constructeur
Player::Player(Transform const& transform, double speed, string const& texturePath) : 
    GameObject{ transform, speed, texturePath, Faction::ALLY } 
{
    setParams();
}

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

void Player::Update(double deltaTime, sf::View const& view, Vector2 windowSize, Vector2 playerPosition, std::vector<std::unique_ptr<GameObject>>* gameObjects, LevelUpdateValues* levelUpdateValues) {
    Vector2 movement{ 0.f, 0.f };

    if (isMovingUp && getPosition().y > view.getCenter().y - windowSize.y/2 + getSpeed() * deltaTime) {
        movement.y -= getSpeed();
    }    
    if (isMovingDown && getPosition().y < view.getCenter().y + windowSize.y / 2 - getSize().y - getSpeed() * deltaTime) {
        movement.y += getSpeed();
    }
    if (isMovingLeft && getPosition().x > getSpeed() * deltaTime) {
        movement.x -= getSpeed();
    }
    if (isMovingRight && getPosition().x < view.getCenter().x + windowSize.x / 2 - getSize().x - getSpeed() * deltaTime) {
        movement.x += getSpeed();
    }
    move(movement*deltaTime);

    // Cooldowns
    updateCooldowns(deltaTime);

    if (isShooting && !isRealoading()) {
        cout << "Shooting" << endl;
        effects.emplace_back(EffectType::RELOAD, shootingTime, 0);

        ResourceManager::playSound("resources/Audio/laserShoot.wav");
        vector<unique_ptr<Projectile>> projectiles = shootProjectile();

        for (auto& projectile : projectiles) {
            gameObjects->push_back(std::move(projectile));
        }
    }
}

void Player::updateCooldowns(double deltaTime) {
    auto it = effects.begin();

    while (it != effects.end()) {
        if (it->cooldown > 0.0) {
            it->cooldown -= deltaTime;
            ++it;
        }
        else {
            switch (it->type)
            {
                using enum EffectType;
                case INVULNERABILITY:
                    isRendered = true;
                    break;
                case RELOAD:
                    break;
                case DAMAGE_BOOST:
                    break;
                case SPEED_BOOST:
                    break;
                case PROJECTILE_MULTIPLICATION:
                    break;
            }
            it = effects.erase(it);
        }
    }

    if (isInvulnerable()) {
        if (blinkCooldown > 0.0) {
            blinkCooldown -= deltaTime;
        }
        else {
            blinkCooldown = blinkTime;
            isRendered = !isRendered;
        }
    }
}

vector<unique_ptr<Projectile>> Player::shootProjectile() const {
    Vector2 projectileSize = { 32, 56 };
    vector<unique_ptr<Projectile>> projectiles;

    cout << "Playze size : " << getSize().x << ", " << getSize().y << endl;

    Vector2 projectilePosition = { getPosition().x + getSize().x / 2 - projectileSize.x / 2, getPosition().y - projectileSize.y };
    Transform projectileTransform = { projectilePosition, projectileSize, 0 };
    string projectileTexturePath = "resources/Sprites/Basic_Projectile.png";

    projectiles.push_back(make_unique<Projectile_Basic>(projectileTransform, 20, projectileTexturePath, 10));

    return projectiles;
}
#pragma endregion Update

// Out of view
bool Player::isOutRenderZone(sf::View const& view, Vector2 windowSize) const { return false; }

// Collision
#pragma region Collision
bool Player::hasCollided(GameObject const& gameObject) const { return false; } // The player cannot do damage by contact

bool Player::onCollissionAction(GameObject& gameObject, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) { return false; }

bool Player::onCollisionActionReaction(Action action, double actionValue, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) {
    if (action == Action::DAMAGE && !isInvulnerable()) {
        healthPoints -= static_cast<int>(actionValue);

        effects.emplace_back(EffectType::INVULNERABILITY, 1, 0 );

        if (healthPoints <= 0) {
            levelUpdateValues->playerKilled = true;
        }
        cout << healthPoints << endl;
        return true;
    }
    return false;
}
#pragma endregion Collision

// Upgrades
void Player::upgrade(Upgrade upgrade) {}

// Getter
double Player::getDamageMultiplier() const { return damageMultiplier; }
double Player::getGoldMultiplier() const { return goldMultiplier; }
bool Player::isInvulnerable() const {
    return std::ranges::any_of(effects, [](Effect effect)
        {
            return effect.type == EffectType::INVULNERABILITY;
        });
}
bool Player::isRealoading() const {
    return std::ranges::any_of(effects, [](Effect effect)
        {
            return effect.type == EffectType::RELOAD;
        });
}

// Setter
void Player::addGold(int gold) { goldCount += gold; }
