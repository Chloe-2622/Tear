#include "Basic_Tear.h"

using namespace std;

void Basic_Tear::setParams() {
	setHealthPoints(100);
	setDamage(10);
	setGoldReward(100);
	setScrollingPenalty(0.1);
}

#pragma region Constructeurs
Basic_Tear::Basic_Tear() :
	Tear()
{}

Basic_Tear::Basic_Tear(Transform const& transform, double speed, string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldReward) :
	Tear(transform, speed, texturePath, healthPoints, scrollingPenalty, damage, goldReward)
{}

Basic_Tear::Basic_Tear(const pugi::xml_node& node) :
	Tear(node)
{
	setParams();
}
#pragma endregion Constructeurs

std::unique_ptr<Tear> Basic_Tear::copy() const {
	return make_unique<Basic_Tear>(*this);
}

void Basic_Tear::hit(Player& player, vector<unique_ptr<GameObject>> const& gameObjects) const {
	if (getPosition().distance(player.getPosition()) < getSize().x) {
		doDamage(player, 1);		 
	}
}