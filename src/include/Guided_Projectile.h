#pragma once

#include "Projectile.h"

class Guided_Projectile : public Projectile
{
public:
    // Constructeurs
    explicit Guided_Projectile();
    ~Guided_Projectile() override = default;
    explicit Guided_Projectile(Transform const& transform, double speed, std::string const& texturePath);

    // Update
    void doDamage(GameObject & gameObject, double playerMultiplier) const override;

};