// #pragma once

#include "GameObject.h"
#include "Tear.h"

class Guided_Tear : public Tear {
public:
	// Constructeurs
	explicit Guided_Tear();
	~Guided_Tear() override = default;
	explicit Guided_Tear(Transform const& transform, double speed, std::string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldReward);
	explicit Guided_Tear(const pugi::xml_node& node);
	explicit Guided_Tear(Guided_Tear const& guided_Tear) = default;
	void setParams();

	std::unique_ptr<Tear> copy() const override;

	void Update(double deltaTime, double scrollingSpeed = 0, float viewPositionY = 0, float windowLenght = 0, Vector2 playerPosition = { 0, 0 }) override;
};