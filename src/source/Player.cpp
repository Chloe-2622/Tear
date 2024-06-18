#include "Player.h"

Player::Player(Transform const& transform, double speed, std::string const& texturePath) : GameObject(transform, speed, texturePath) {}

void Player::UpdatePlayer(double deltaTime, float viewPositionY, float windowLength, float windowWidth, std::vector<std::unique_ptr<Projectile>>& projectiles) {
    Vector2 movement(0.f, 0.f);
    if (isMovingUp && getPosition().y > viewPositionY) {
        movement.y -= getSpeed();
    }
    if (isMovingDown && getPosition().y < viewPositionY + windowLength - getSize().y) {
        movement.y += getSpeed();
    }
    if (isMovingLeft && getPosition().x > 0) {
        movement.x -= getSpeed();
    }
    if (isMovingRight && getPosition().x < windowWidth - getSize().x) {
        movement.x += getSpeed();
    }
    move(movement);

    if (shootingCooldown > 0.0) {
        shootingCooldown -= deltaTime;
    }
    if (isShooting && shootingCooldown <= 0.0) {
        std::cout << "Shooting" << std::endl;
        shootingCooldown = shootingSpeed;
        shootProjectile(projectiles);
    }
    
};

void Player::handleInput(sf::Keyboard::Key keyPressed, bool isPressed) {
    if (keyPressed == sf::Keyboard::Z) {
        isMovingUp = isPressed;
    }
    if (keyPressed == sf::Keyboard::S) {
        isMovingDown = isPressed;
    }
    if (keyPressed == sf::Keyboard::Q) {
        isMovingLeft = isPressed;
    }
    if (keyPressed == sf::Keyboard::D) {
        isMovingRight = isPressed;
    }
    if (keyPressed == sf::Keyboard::Space) {
        isShooting = isPressed;
    }
}

void Player::shootProjectile(std::vector<std::unique_ptr<Projectile>>& projectiles) {
    Vector2 projectileSize = {32, 56};
    std::cout << "Playze size : " << getSize().x << ", " << getSize().y << std::endl;
    Vector2 projectilePosition = {getPosition().x + getSize().x/2 - projectileSize.x/2, getPosition().y - projectileSize.y};
    Transform projectileTransform = {projectilePosition, projectileSize, 0};
    std::string projectileTexturePath = "resources/Sprites/Basic_Projectile.png";
    std::unique_ptr<Projectile> projectile = std::make_unique<Basic_Projectile>(projectileTransform, 100, projectileTexturePath);
    projectiles.push_back(std::move(projectile));
}
