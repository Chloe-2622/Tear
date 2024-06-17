#include "Player.h"


Player::Player() : GameObject() {};

Player::Player(Transform transform, double speed, std::string texturePath) :
    GameObject(transform, speed, texturePath)
{}

void Player::Update(double deltaTime) {};
