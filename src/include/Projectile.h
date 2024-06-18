#pragma once

#include "GameObject.h"

class Tear;

class Projectile : public GameObject {
    public:
        Projectile() = default;
        explicit                    Projectile(Transform const &transform, double speed, std::string const &texturePath, double damage);
    
        // Update
        void                        supressOffset(Vector2 offset) override;
    
        // Out of view
        bool                        isOutofView(sf::FloatRect currentViewBox) const override;
    
        // Damages
        bool                        hasCollided(GameObject const& gameObject) const override;
        bool                        doDamage(GameObject& gameObject, double playerMultiplier) const override; // True si kill
        bool                        takeDamage(double damages) override; // True si mort

        // Setter
        void                        setDamage(double newDamage);

    private:
        double                      damage;
};