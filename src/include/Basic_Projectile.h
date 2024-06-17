#pragma once

#include "Projectile.h"

class Basic_Projectile : public Projectile {
public:
    // Constructeurs
    explicit Basic_Projectile();
    ~Basic_Projectile() override = default;
    explicit Basic_Projectile(Transform const& transform, double speed, std::string const& texturePath, double damage);
    explicit Basic_Projectile(const pugi::xml_node& node);
    explicit Basic_Projectile(Basic_Projectile const& basic_projectile) = default;
    void setParams();

    // Construct Level
    std::unique_ptr<Projectile> copy() const override;

    // Update
    void Update(double deltaTime, double scrollingSpeed, float viewPositionY, float windowLenght, Vector2 playerPosition) override;
    void doDamage(const std::vector<std::unique_ptr<Tear>> &tears) override;
};