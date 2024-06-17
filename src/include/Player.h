#pragma once

#include "GameObject.h"
#include "Shop.h"

class Player : public GameObject {
    public:
        Player();
        Player(Transform transform, double speed, std::string texturePath);






        void shootProjectile();
        bool takeDamage(double damage) override {return false;};
        void upgrade(Upgrade upgrade);

        // Override
        void        UpdatePlayer(double deltaTime, double scrollingSpeed, float viewPositionY, float windowLength, float windowWidth);

        void handleInput(sf::Keyboard::Key keyPressed, bool isPressed);

    private:
        // Health
        int healthPoint = 100;

        // Damage
        double damageMultiplier = 1.0;

        // Gold
        int goldCount = 0;
        double goldMultiplier = 1.0;

        // Projectiles
        int projectileDuplication = 1.0;

        bool hasSetPlayerEnd = false;

        // Movements
        bool isMovingUp = false;
        bool isMovingDown = false;
        bool isMovingLeft = false;
        bool isMovingRight = false;
        
};