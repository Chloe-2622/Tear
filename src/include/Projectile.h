#pragma once

#include "GameObject.h"
#include <iostream>
#include <sstream>

class Tear;

class Projectile : public GameObject {
    public:
        Projectile() = default;
        explicit                    Projectile(Transform const &transform, double speed, std::string const &texturePath, double damage);
    
        // Update
        void                        followView(Vector2 movement) override;
        void                        supressViewOffset(Vector2 offset) override;
    
        // Out of view
        bool                        isOutofView(sf::View const& view, Vector2 windowSize) const override;
    
        // Damages
        bool                        hasCollided(GameObject const& gameObject) const override;
        bool                        doDamage(GameObject& gameObject, double playerMultiplier) const override; // True si kill
        bool                        takeDamage(double damages) override; // True si mort

        // Setter
        void                        setDamage(double newDamage);

        // Debug
        std::string				    dump(std::string const& indent = "") const override;


    private:
        double                      damage;
};