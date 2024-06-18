#include "Tear_River.h"

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

// Update
unique_ptr<GameObject> Tear_River::Update(double deltaTime, sf::View const& view, Vector2 windowSize, Vector2 playerPosition) {
	// Scrolling de la texture a implémenté si il y a le temps
	return nullptr;
};

// Damages
bool Tear_River::takeDamage(double damages) { // Une rivière ne peut pas être tapée
	return false;
}
