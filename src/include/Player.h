#pragma once

#include "GameObject.h"
#include "Shop.h"
#include "Projectile_Basic.h"

class Player : public GameObject {
    public:
        Player() = default;
        explicit Player(Transform const& transform, double speed, std::string const& texturePath);

        // Render
        void                            Render(sf::RenderWindow& window) const override;

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
        double                          getDamageMultiplier() const;
        double                          getGoldMultiplier() const;

        // Setter
        void                            addGold(int gold);

        //Debug
        bool						    operator==(const Player&) const = default;


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
        double                      shootingTime = 0.5;
        double                      shootingCooldown = 0.0;
        double                      shootingSpeed = 0.2;
        
        double                      invulnerabilityTime = 1;
        double                      invulnerabilityCooldown = 0.0;
        double                      blinkTime = 0.1;
        double                      blinkCooldown = 0.0;
        bool                        isRendered = true;
};