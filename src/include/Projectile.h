#pragma once

#include "GameObject.h"

class Tear;

class Projectile : public GameObject
{
public:
    Projectile() = default;
    explicit                    Projectile(Transform const &transform, double speed, std::string const &texturePath);

    bool		                isOutofView(sf::FloatRect currentViewBox) const override;

    void                        UpdateProjectile(double deltaTime, float viewPositionY, float windowLength, float windowWidth);

    bool                        takeDamage(double damages) override;
    virtual void                doDamage(const std::vector<std::unique_ptr<Tear>> &tears);

private:
    double                      damage = 10;
};