#include "Tear.h"

using namespace std;

// Constructeurs
#pragma region Constructeurs
Tear::Tear(Transform const& transform, double speed, string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldReward):
	GameObject{transform, speed, texturePath, Faction::Enemie},
	healthPoints{ healthPoints },
	scrollingPenalty{ scrollingPenalty },
	damage{ damage },
	goldReward{ goldReward }
{}

Tear::Tear(const pugi::xml_node& node, std::string const& texturePath) :
	GameObject{ node, 0, texturePath, Faction::Enemie}
{}
#pragma endregion Constructeurs

// Update
void Tear::supressOffset(Vector2 offset) {/* Les tears ne se déplacent pas dans le niveau, il n'y a donc pas besoin de les bouger avec la camera*/};

// Out of view
#pragma region Out of view
bool Tear::isOutofView(sf::FloatRect currentViewBox) const { return getPosition().y > currentViewBox.top + currentViewBox.height; }

double Tear::exitViewValue() const { return scrollingPenalty; }
#pragma endregion Out of view

// Damages
#pragma region Damages
bool Tear::hasCollided(GameObject const& gameObject) const {
	return getPosition().distance(gameObject.getPosition()) < getSize().x;
}

bool Tear::doDamage(GameObject& gameObject, double playerMultiplier) const {
	return gameObject.takeDamage(damage);
}

bool Tear::takeDamage(double damages) {
	healthPoints -= static_cast<int>(damages);
	return healthPoints <= 0;
}
#pragma endregion Damages

// Setter
#pragma region Setter
void Tear::setHealthPoints(int healthPointsNew) { healthPoints = healthPointsNew; }
void Tear::setScrollingPenalty(double scrollingPenaltyNew) { scrollingPenalty = scrollingPenaltyNew; }
void Tear::setDamage(double damageNew) { damage = damageNew; }
void Tear::setGoldReward(int goldRewardNew) { goldReward = goldRewardNew; }
#pragma endregion Setter