#pragma once

#include "Tear.h"

class Tear_Basic : public Tear {
	public:
		explicit Tear_Basic() = default;
		~Tear_Basic() override = default;
		explicit Tear_Basic(Transform const& transform, double speed, std::string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldreward);
		explicit Tear_Basic(const pugi::xml_node& node);
		explicit Tear_Basic(Tear_Basic const& tear_Basic) = default;
		void setParams();

		// Construct Level
		std::unique_ptr<Tear>		copy() const override;

		// Debug
		std::string					dump(std::string const& indent = "") const override;
};