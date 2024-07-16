#include "GameObjects/Projectiles/Projectile_Guided.h"

using namespace std;

// Param�tres
void Projectile_Guided::setParams() {
	// GameObject
	setSpeed(100);
	setTexturePath("resources/Sprites/Basic_Projectile.png");

	//Projectile
	setDamage(10);

	// Booleans
	setFriendlyFire(false);
	setFollowingView(true);
	setDestroyOnHit(true);
}

// Constructeurs
Projectile_Guided::Projectile_Guided(Transform const& transform, double speed, std::string const& texturePath, double damage) :
	Projectile{ transform, speed, texturePath, damage }
{
	setParams();
}

// Update
void Projectile_Guided::Update(double deltaTime, sf::View const& view, Vector2 windowSize, Vector2 playerPosition, std::vector<std::unique_ptr<GameObject>>* gameObjects, LevelUpdateValues* levelUpdateValues) {
	move({ 0, -10 * getSpeed() * deltaTime });
	GameObject::Update(deltaTime, view, windowSize, playerPosition, gameObjects, levelUpdateValues);
};