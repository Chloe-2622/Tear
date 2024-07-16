#pragma once

#include <iostream>
#include <sstream>
#include "pugixml.hpp"
#include "GameObjects/GameObject.h"

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
	
		// Out of view
		bool								isOutRenderZone(sf::View const& view, Vector2 windowSize) const override;
		void								exitRenderZone(LevelUpdateValues* levelUpdateValues) override;
	
		// Collision
		bool								onCollissionAction(GameObject& gameObject, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) override;
		bool								onCollisionActionReaction(Action action, double actionValue, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) override;

	
		// Setter
		void								setHealthPoints(int healthPointsNew);
		void								setScrollingPenalty(double scrollingPenaltyNew);
		void								setDamage(double damageNew);
		void								setGoldReward(int goldRewardNew);

		// Debug
		std::string							dump(std::string const& indent = "") const override;


	private:
		int									healthPoints = 100;
		double								scrollingPenalty = 1;
		double								damage = 10;
		int									goldReward = 10;
};