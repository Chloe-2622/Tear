#include "Player.h"


Player::Player() : GameObject() {
    healthPoint = 100;
    damageMultiplier = 1.0;
    goldCount = 0;
    goldMultiplier = 1.0;
    projectileDuplication = 1;
};

Player::Player(Transform transform, double speed) : GameObject(transform, speed) {
    healthPoint = 100;
    damageMultiplier = 1.0;
    goldCount = 0;
    goldMultiplier = 1.0;
    projectileDuplication = 1;
};




void Player::Update(double deltaTime) {};

