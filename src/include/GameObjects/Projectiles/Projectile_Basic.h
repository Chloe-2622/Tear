#pragma once

#include "GameObjects/Projectiles/Projectile.h"

class Projectile_Basic : public Projectile {
public:
	explicit Projectile_Basic() = default;
	~Projectile_Basic() override = default;
	explicit Projectile_Basic(Transform const& transform, double speed, std::string const& texturePath, double damage);
	void setParams();

	// Update
	void		Update(double deltaTime, sf::View const& view, Vector2 windowSize, Vector2 playerPosition, std::vector<std::unique_ptr<GameObject>>* gameObjects, LevelUpdateValues* levelUpdateValues) override;
};