#pragma once

#include "GameObject.h"
#include "Shop.h"

class Player : public GameObject {
    public:
        Player() = default;
        explicit Player(Transform transform, double speed, std::string texturePath);

        void                        shootProjectile();
        bool                        takeDamage(double damage) override {return false;};
        void                        upgrade(Upgrade upgrade);

        // Override
        void                        UpdatePlayer(double deltaTime, double scrollingSpeed, float viewPositionY, float windowLength, float windowWidth);
        virtual unique_ptr<GameObject> hit(Player& player, std::vector<std::unique_ptr<GameObject>> const& gameObjects) const override {};


        void                        handleInput(sf::Keyboard::Key keyPressed, bool isPressed);

    private:
        int                         healthPoint = 100;

        double                      damageMultiplier = 1.0;

        int                         goldCount = 0;
        double                      goldMultiplier = 1.0;

        int                         projectileDuplication = 1.0;

        bool                        isMovingUp = false;
        bool                        isMovingDown = false;
        bool                        isMovingLeft = false;
        bool                        isMovingRight = false;
        
};