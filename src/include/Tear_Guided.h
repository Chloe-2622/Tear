#pragma once

#define _USE_MATH_DEFINES
#include "Tear.h"
#include <math.h>

class Tear_Guided : public Tear {
	public:
		explicit Tear_Guided() = default;
		~Tear_Guided() override = default;
		explicit Tear_Guided(Transform const& transform, double speed, std::string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldreward);
		explicit Tear_Guided(const pugi::xml_node& node);
		explicit Tear_Guided(Tear_Guided const& tear_Guided) = default;
		void setParams();
	
		// Construct Level
		std::unique_ptr<Tear>			copy() const override;
	
		// Update
		std::unique_ptr<GameObject>		Update(double deltaTime, sf::View const& view, Vector2 windowSize, Vector2 playerPosition) override;
	
	private:
		Vector2 playerPosition;
};