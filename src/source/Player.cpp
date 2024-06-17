#include "Player.h"


Player::Player() : GameObject() {};

Player::Player(Transform transform, double speed, std::string texturePath) :
    GameObject(transform, speed, texturePath)
{}

void Player::UpdatePlayer(double deltaTime, double scrollingSpeed, float viewPositionY, float windowLength, float windowWidth) {
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
}
