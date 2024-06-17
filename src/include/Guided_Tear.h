#pragma once

#include "GameObject.h"
#include "Tear.h"
#include "Player.h"

class Guided_Tear : public Tear {
public:
	// Constructeurs
	explicit Guided_Tear();
	~Guided_Tear() override = default;
	explicit Guided_Tear(Transform const& transform, double speed, string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldReward);
	explicit Guided_Tear(const pugi::xml_node& node, Player player);
	explicit Guided_Tear(Guided_Tear const& guided_Tear);

	// Construct Level
	std::unique_ptr<Tear> copy() const override;

	//void		Update() override;
};