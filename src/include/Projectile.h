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
    void                        doDamage(const Tear& tear) {};
    void                        doDamage(GameObject& gameObject, double playerMultiplier) const override {};

    void hit(Player& player, std::vector<std::unique_ptr<GameObject>> const& gameObjects) const override {};

};