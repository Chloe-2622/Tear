#pragma once

#include "Projectile.h"

class Projectile_Basic : public Projectile {
public:
	explicit Projectile_Basic() = default;
	~Projectile_Basic() override = default;
	explicit Projectile_Basic(Transform const& transform, double speed, std::string const& texturePath, double damage);
	void setParams();

	// Update
	std::unique_ptr<GameObject>		Update(double deltaTime, sf::FloatRect currentViewBox, Vector2 windowSize, Vector2 playerPosition) override;

};