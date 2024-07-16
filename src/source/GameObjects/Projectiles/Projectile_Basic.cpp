#include "GameObjects/Projectiles/Projectile_Basic.h"

using namespace std;

// Paramètres
void Projectile_Basic::setParams() {
	// GameObject
	setSpeed(100);
	setTexturePath("resources/Sprites/Basic_Projectile.png");

	//Projectile
	setDamage(100);

	// Booleans
	setFriendlyFire(false);
	setFollowingView(true);
	setDestroyOnHit(true);
}

// Constructeurs
Projectile_Basic::Projectile_Basic(Transform const& transform, double speed, std::string const& texturePath, double damage) :
	Projectile{ transform, speed, texturePath, damage }
{
	setParams();
}

// Update
void Projectile_Basic::Update(double deltaTime, sf::View const& view, Vector2 windowSize, Vector2 playerPosition, std::vector<std::unique_ptr<GameObject>>* gameObjects, LevelUpdateValues* levelUpdateValues) {
	move({ 0, -10 * getSpeed() * deltaTime });
	GameObject::Update(deltaTime, view, windowSize, playerPosition, gameObjects, levelUpdateValues);
};