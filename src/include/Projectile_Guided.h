#pragma once

#include "Projectile.h"

class Projectile_Guided : public Projectile {
public:
	explicit Projectile_Guided() = default;
	~Projectile_Guided() override = default;
	explicit Projectile_Guided(Transform const& transform, double speed, std::string const& texturePath, double damage);
	void setParams();

	// Update
	std::unique_ptr<GameObject>		Update(double deltaTime, sf::View const& view, Vector2 windowSize, Vector2 playerPosition) override;

};