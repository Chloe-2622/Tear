#include "Tear.h"

using namespace std;

#pragma region Constructeurs
Tear::Tear() :
	GameObject()
{}

Tear::Tear(Transform const& transform, double speed, string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldReward):
	GameObject(transform, speed, texturePath),
	healthPoints{ healthPoints },
	scrollingPenalty{ scrollingPenalty },
	damage{ damage },
	goldReward{ goldReward }
{}

Tear::Tear(const pugi::xml_node& node) :
	GameObject{ node, 0, "resources/Sprites/Basic_Tear.png" }
{}

Tear::Tear(Tear const& tear) :
	GameObject(tear),
	healthPoints{ tear.healthPoints },
	scrollingPenalty{ tear.scrollingPenalty },
	damage{ tear.damage },
	goldReward{ tear.goldReward }
{}
#pragma endregion Constructeurs

std::unique_ptr<Tear> Tear::copy() const{
	return make_unique<Tear>(*this);
}

bool Tear::isOutofView(float const viewBottomBoarder) const {
	//cout << "Bottom: " << viewBottomBoarder << ", Position: " << transform.position.y << "\n";

	return getPosition().y >= viewBottomBoarder;
}

double Tear::exitView() const {
	return scrollingPenalty;
}

bool Tear::hit(Player const& player, vector<unique_ptr<GameObject>> const& gameObjects) const {
	return (abs(player.getPosition().x - getPosition().x) < getSize().x) && (abs(player.getPosition().y - getPosition().y) < getSize().y);
}

void Tear::doDamage(GameObject gameObject, double playerMultiplier) const { gameObject.takeDamage(damage * playerMultiplier); }
bool Tear::takeDamage(double damages) {
	healthPoints -= (int)damages;
	return healthPoints < 0;
}

void Tear::setScrollingPenalty(double scrollingPenaltyNew) { scrollingPenalty = scrollingPenaltyNew; }
