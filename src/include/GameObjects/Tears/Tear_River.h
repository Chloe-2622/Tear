#pragma once

#include "GameObjects/Tears/Tear.h"

class Tear_River : public Tear {
public:
	explicit Tear_River() = default;
	~Tear_River() override = default;
	explicit Tear_River(Transform const& transform, double speed, std::string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldreward);
	explicit Tear_River(const pugi::xml_node& node);
	explicit Tear_River(Tear_River const& tear_River) = default;
	void setParams();

	// Construct Level
	std::unique_ptr<Tear>			copy() const override;

	// Collsion
	bool							onCollisionActionReaction(Action action, double actionValue, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) override;
};