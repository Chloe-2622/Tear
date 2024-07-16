#include "GameObjects/Tears/Tear_River.h"

using namespace std;

// Paramètres
void Tear_River::setParams() {
	// GameObject
	setSpeed(0);
	setTexturePath("resources/Sprites/Tears/River_Tear.png");

	//Tear
	setHealthPoints(100);
	setScrollingPenalty(0);
	setDamage(10);
	setGoldReward(0);

	// Booleans
	setFriendlyFire(true);
	setFollowingView(false);
	setDestroyOnHit(true);
}

// Constructeurs
#pragma region Constructeurs
Tear_River::Tear_River(Transform const& transform, double speed, string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldReward) :
	Tear{ transform, speed, texturePath, healthPoints, scrollingPenalty, damage, goldReward }
{}

Tear_River::Tear_River(const pugi::xml_node& node) :
	Tear{ node, "resources/Sprites/River_Tear.png" }
{
	setParams();
}
#pragma endregion Constructeurs

// Construct Level
unique_ptr<Tear> Tear_River::copy() const { return make_unique<Tear_River>(*this); }

// Collision
bool Tear_River::onCollisionActionReaction(Action action, double actionValue, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) { // Une rivière ne peut pas être tapée
	if (action == Action::DAMAGE) {
		return true;
	}
	return false;
}
