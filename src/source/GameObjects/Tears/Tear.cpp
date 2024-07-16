#include "GameObjects/Tears/Tear.h"

using namespace std;

// Constructeurs
#pragma region Constructeurs
Tear::Tear(Transform const& transform, double speed, string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldReward):
	GameObject{transform, speed, texturePath, Faction::ENEMIE},
	healthPoints{ healthPoints },
	scrollingPenalty{ scrollingPenalty },
	damage{ damage },
	goldReward{ goldReward }
{}

Tear::Tear(const pugi::xml_node& node, std::string const& texturePath) :
	GameObject{ node, 0, texturePath, Faction::ENEMIE}
{}
#pragma endregion Constructeurs

// Out of view
#pragma region Out of view
bool Tear::isOutRenderZone(sf::View const& view, Vector2 windowSize) const {
	return getPosition().y > view.getCenter().y + windowSize.y/2;
}

void Tear::exitRenderZone(LevelUpdateValues* levelUpdateValues) { 
	levelUpdateValues->scrollingPenalty += scrollingPenalty;
	GameObject::exitRenderZone(levelUpdateValues);
}
#pragma endregion Out of view

// Damages
#pragma region Collision
bool Tear::onCollissionAction(GameObject& gameObject, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) {
	return gameObject.onCollisionActionReaction(Action::DAMAGE, damage, playerModifiersValue, levelUpdateValues);
}

bool Tear::onCollisionActionReaction(Action action, double actionValue, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) {
	if (action == Action::DAMAGE) {
		healthPoints -= static_cast<int>(actionValue);
		if (healthPoints <= 0) {
			levelUpdateValues->goldEarned += static_cast<int>(goldReward * playerModifiersValue.goldMultiplier);
			levelUpdateValues->killedObjects.push_back(this);
		}
		return true;
	}
	return false;
}
#pragma endregion Collision

// Setter
#pragma region Setter
void Tear::setHealthPoints(int healthPointsNew) { healthPoints = healthPointsNew; }
void Tear::setScrollingPenalty(double scrollingPenaltyNew) { scrollingPenalty = scrollingPenaltyNew; }
void Tear::setDamage(double damageNew) { damage = damageNew; }
void Tear::setGoldReward(int goldRewardNew) { goldReward = goldRewardNew; }
#pragma endregion Setter

// Debug
std::string	Tear::dump(std::string const& indent) const {
	ostringstream oss;
	oss << "HP: " << healthPoints << endl;
	return oss.str();
}
