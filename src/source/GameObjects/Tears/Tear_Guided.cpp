#include "GameObjects/Tears/Tear_Guided.h"

using namespace std;

// Param�tres
void Tear_Guided::setParams() {
	// GameObject
	setSpeed(200);
	setTexturePath("resources/Sprites/Tears/Guided_Tear.png");

	//Tear
	setHealthPoints(100);
	setScrollingPenalty(30);
	setDamage(50);
	setGoldReward(100);

	// Booleans
	setFriendlyFire(true);
	setFollowingView(false);
	setDestroyOnHit(true);
}

// Constructeurs
#pragma region Constructeurs
Tear_Guided::Tear_Guided(Transform const& transform, double speed, string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldReward) :
	Tear{ transform, speed, texturePath, healthPoints, scrollingPenalty, damage, goldReward }
{}

Tear_Guided::Tear_Guided(const pugi::xml_node& node) :
	Tear{ node, "resources/Sprites/Guided_Tear.png" }
{
	setParams();
}
#pragma endregion Constructeurs

// Construct Level
unique_ptr<Tear> Tear_Guided::copy() const { return make_unique<Tear_Guided>(*this); }

// Update
void Tear_Guided::Update(double deltaTime, sf::View const& view, Vector2 windowSize, Vector2 playerPosition,
											std::vector<std::unique_ptr<GameObject>>* gameObjects,
											LevelUpdateValues* levelUpdateValues) {
	// Sets new rotation to face the player
	setRotation(-90 + atan2(playerPosition.y - getPosition().y, playerPosition.x - getPosition().x) * 180 / M_PI);

	Vector2 direction = playerPosition - getPosition();
	direction.normalize();

	move(direction * getSpeed() * deltaTime);
};