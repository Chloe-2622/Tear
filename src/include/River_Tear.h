#pragma once

#include "GameObject.h"
#include "Tear.h"

class River_Tear : public Tear {
public:
	// Constructeurs
	explicit River_Tear();
	~River_Tear() override = default;
	explicit River_Tear(Transform const& transform, double speed, std::string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldReward);
	explicit River_Tear(const pugi::xml_node& node);
	explicit River_Tear(River_Tear const& river_tear);

	// Construct Level
	std::unique_ptr<Tear> copy() const override;

	void Update(double deltaTime, double scrollingSpeed = 0, float viewPositionY = 0, float windowLenght = 0, Vector2 playerPosition = { 0, 0 }) override;
};