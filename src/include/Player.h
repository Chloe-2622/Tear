#pragma once

#include "GameObject.h"
#include "Shop.h"
#include "Projectile.h"

class Player : public GameObject {
    public:
        Player() = default;
        explicit Player(Transform const& transform, double speed, std::string const& texturePath);

        void                        shootProjectile(std::vector<std::unique_ptr<Projectile>>& projectiles);
        void                        doDamage(GameObject& gameObject, double playerMultiplier) const override {};
        bool                        takeDamage(double damage) override {return false;};
        void                        upgrade(Upgrade upgrade);

        // Override
        //virtual unique_ptr<GameObject> hit(Player& player, std::vector<std::unique_ptr<GameObject>> const& gameObjects) const override {};
        void                        UpdatePlayer(double deltaTime, float viewPositionY, float windowLength, float windowWidth, std::vector<std::unique_ptr<Projectile>>& projectiles);
        void hit(Player& player, std::vector<std::unique_ptr<GameObject>> const& gameObjects) const override {};


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

        bool                        isShooting = false;
        double                      shootingCooldown = 0.0;
        
};