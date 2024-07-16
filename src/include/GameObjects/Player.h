#pragma once

#include "GameObjects/GameObject.h"
#include "GameObjects/Projectiles/Projectile_Basic.h"
#include "Scenes/Shop.h"

enum class EffectType {
    INVULNERABILITY,
    RELOAD,
    DAMAGE_BOOST,
    SPEED_BOOST,
    PROJECTILE_MULTIPLICATION
};

struct Effect {
    EffectType type;
    double cooldown;
    double value;
};

class Player : public GameObject {
    public:
        Player() = default;
        explicit Player(Transform const& transform, double speed, std::string const& texturePath);
        void        setParams();

        // Render
        void                                        Render(sf::RenderWindow& window) const override;

        // Update
        void                                        handleInput(sf::Keyboard::Key key, bool isPressed);
        void                                        Update(double deltaTime, sf::View const& view, Vector2 windowSize, Vector2 playerPosition, std::vector<std::unique_ptr<GameObject>>* gameObjects, LevelUpdateValues* levelUpdateValues) override;
        void                                        updateCooldowns(double deltaTime);
        std::vector<std::unique_ptr<Projectile>>    shootProjectile() const;

        // Out of view
        bool                                        isOutRenderZone(sf::View const& view, Vector2 windowSize) const override;

        // Collision
        bool                                        hasCollided(GameObject const& gameObject) const override;
        bool							            onCollissionAction(GameObject& gameObject, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) override;
        bool							            onCollisionActionReaction(Action action, double actionValue, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) override;


        // Upgrades
        void                                        upgrade(Upgrade upgrade);

        // Getter
        double                                      getDamageMultiplier() const;
        double                                      getGoldMultiplier() const;
        bool                                        isInvulnerable() const;
        bool                                        isRealoading() const;

        // Setter
        void                                        addGold(int gold);

    private:
        int                                         healthPoints = 100;

        double                                      damageMultiplier = 1.0;

        int                                         goldCount = 0;
        double                                      goldMultiplier = 1.0;

        int                                         projectileDuplication = 1.0;

        bool                                        isMovingUp = false;
        bool                                        isMovingDown = false;
        bool                                        isMovingLeft = false;
        bool                                        isMovingRight = false;

        bool                                        isShooting = false;
        double                                      shootingTime = 0.2;
        
        double                                      blinkTime = 0.1;
        double                                      blinkCooldown = 0.0;
        bool                                        isRendered = true;

        std::vector<Effect>                         effects;
};