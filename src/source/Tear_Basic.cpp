#include "Tear_Basic.h"

using namespace std;

// Paramètres
void Tear_Basic::setParams() {
	// GameObject
	setSpeed(0);
	setTexturePath("resources/Sprites/Tears/Basic_Tear.png");

	//Tear
	setHealthPoints(100);
	setScrollingPenalty(0.1);
	setDamage(10);
	setGoldReward(100);
}

// Constructeurs
#pragma region Constructeurs
Tear_Basic::Tear_Basic(Transform const& transform, double speed, string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldReward) :
	Tear{ transform, speed, texturePath, healthPoints, scrollingPenalty, damage, goldReward }
{}

Tear_Basic::Tear_Basic(const pugi::xml_node& node) :
	Tear{ node, "resources/Sprites/Basic_Tear.png" }
{
	setParams();
}
#pragma endregion Constructeurs

// Construct Level
unique_ptr<Tear> Tear_Basic::copy() const { return make_unique<Tear_Basic>(*this); }