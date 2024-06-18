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
void Tear::followView(Vector2 movement) { /*Les larmes ne suivent pas la camera*/ }
void Tear::supressViewOffset(Vector2 offset) {/* Les tears ne se déplacent pas dans le niveau, il n'y a donc pas besoin de les bouger avec la camera*/};

// Out of view
#pragma region Out of view
bool Tear::isOutofView(sf::View const& view, Vector2 windowSize) const { 
	return getPosition().y > view.getCenter().y + windowSize.y/2;
}

double Tear::exitViewValue() const { return scrollingPenalty; }
#pragma endregion Out of view

// Damages
#pragma region Damages
bool Tear::hasCollided(GameObject const& gameObject) const {
	// Same line on X
	if (gameObject.getPosition().x < getPosition().x + getSize().x && gameObject.getPosition().x + gameObject.getSize().x > getPosition().x) {

		// Same column on Y 
		return gameObject.getPosition().y < getPosition().y + getSize().y && gameObject.getPosition().y + gameObject.getSize().y > getPosition().y;
	}
	return false;
}

bool Tear::doDamage(GameObject& gameObject, double playerMultiplier) const {
	return gameObject.takeDamage(damage);
}

bool Tear::takeDamage(double damages) {
	healthPoints -= static_cast<int>(damages);
	return healthPoints <= 0;
}

int Tear::killReward(double playerMultiplier) const { return static_cast<int>(goldReward * playerMultiplier); }

#pragma endregion Damages

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
