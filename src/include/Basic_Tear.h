#pragma once

#include "Tear.h"

class Basic_Tear : public Tear {
public:
	// Constructeurs
	explicit Basic_Tear();
	~Basic_Tear() override = default;
	explicit Basic_Tear(Transform const& transform, double speed, std::string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldreward);
	explicit Basic_Tear(const pugi::xml_node& node);
	explicit Basic_Tear(Basic_Tear const& basic_tear) = default;
	void setParams();

	// Construct Level
	std::unique_ptr<Tear> copy() const override;

	// Update
	void Update(double deltaTime, double scrollingSpeed, float viewPositionY, float windowLenght, Vector2 playerPosition) override {/*Basic tear do not update*/ };
	//unique_ptr<GameObject> hit(Player& player, std::vector<std::unique_ptr<GameObject>> const& gameObjects) const override;
};