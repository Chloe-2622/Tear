#pragma once

#include <iostream>
#include <sstream>
#include "GameObjects/GameObject.h"

class Tear;

class Projectile : public GameObject {
    public:
        Projectile() = default;
        explicit        Projectile(Transform const &transform, double speed, std::string const &texturePath, double damage);
    
        // Out of view
        bool            isOutRenderZone(sf::View const& view, Vector2 windowSize) const override;
    
        // Collision
        bool            onCollissionAction(GameObject& gameObject, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) override;
        bool            onCollisionActionReaction(Action action, double actionValue, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) override;

        // Setter
        void            setDamage(double newDamage);

        // Debug
        std::string		dump(std::string const& indent = "") const override;


    private:
        double          damage;
};