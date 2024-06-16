#pragma once

#include "GameObject.h"
#include "Shop.h"

class Player : public GameObject {
    public:
        Player();
        Player(Transform transform, double speed);

        void shootProjectile();
        bool takeDamage(double damage);
        void upgrade(Upgrade upgrade);

        // Override
        void Update(double deltaTime) override;

    private:
        // Health
        int healthPoint;

        // Damage
        double damageMultiplier;

        // Gold
        int goldCount;
        double goldMultiplier;

        // Projectiles
        int projectileDuplication;
        
};