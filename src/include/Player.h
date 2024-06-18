#pragma once

#include "GameObject.h"
#include "Shop.h"
#include "Projectile.h"

class Player : public GameObject {
    public:
        Player() = default;
        explicit Player(Transform const& transform, double speed, std::string const& texturePath);

        // Update
        void                            handleInput(sf::Keyboard::Key key, bool isPressed);
        std::unique_ptr<GameObject>     Update(double deltaTime, sf::View const& view, Vector2 windowSize, Vector2 playerPosition) override;
        std::unique_ptr<Projectile>     shootProjectile() const;
        void                            followView(Vector2 movement) override;
        void                            supressViewOffset(Vector2 offset) override;

        // Out of view
        bool                            isOutofView(sf::View const& view, Vector2 windowSize) const override;

        // Damages
        bool                            hasCollided(GameObject const& gameObject) const override;
        bool                            doDamage(GameObject& gameObject, double playerMultiplier) const override;
        bool                            takeDamage(double damages) override; // True si mort

        // Upgrades
        void                            upgrade(Upgrade upgrade);

        // Getter
        double                         getDamageMultiplier() const;



    private:
        int                         healthPoints = 100;

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