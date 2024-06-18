#pragma once

#include "GameObject.h"
#include "pugixml.hpp"


class Tear : public GameObject {
	public:
		// Constructeurs
		explicit Tear() = default;
		~Tear() override = default;
		explicit Tear(Transform const& transform, double speed, std::string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldreward);
		explicit Tear(const pugi::xml_node& node, std::string const& texturePath);
		explicit Tear(Tear const& tear) = default;
	
		// Construct Level
		virtual std::unique_ptr<Tear>		copy() const = 0;
	
		// Update
		void								supressOffset(Vector2 offset) override;
	
		// Out of view
		bool								isOutofView(sf::FloatRect currentViewBox) const override;
		double								exitViewValue() const override;
	
		// Damages
		bool								hasCollided(GameObject const& gameObject) const override;
		bool                                doDamage(GameObject& gameObject, double playerMultiplier) const override; // True si kill
		bool                                takeDamage(double damages) override; // True si mort
	
		// Getter
		void								setHealthPoints(int healthPointsNew);
		void								setScrollingPenalty(double scrollingPenaltyNew);
		void								setDamage(double damageNew);
		void								setGoldReward(int goldRewardNew);
		
	private:
		int									healthPoints = 100;
		double								scrollingPenalty = 1;
		double								damage = 10;
		int									goldReward = 10;
};