#pragma once

#include "Projectile.h"

class Basic_Projectile : public Projectile {
public:
    // Constructeurs
    explicit Basic_Projectile();
    ~Basic_Projectile() override = default;
    explicit Basic_Projectile(Transform const& transform, double speed, std::string const& texturePath);

    // Update
    void doDamage(GameObject & gameObject, double playerMultiplier) const override {};
};