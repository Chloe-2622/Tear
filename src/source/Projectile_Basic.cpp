#include "Projectile_Basic.h"

using namespace std;

// Paramètres
void Projectile_Basic::setParams() {
	// GameObject
	setSpeed(100);
	setTexturePath("resources/Sprites/Basic_Projectile.png");

	//Projectile
	setDamage(10);
}

// Constructeurs
Projectile_Basic::Projectile_Basic(Transform const& transform, double speed, std::string const& texturePath, double damage) :
	Projectile{ transform, speed, texturePath, damage }
{
	setParams();
}

// Update
unique_ptr<GameObject> Projectile_Basic::Update(double deltaTime, sf::View const& view, Vector2 windowSize, Vector2 playerPosition) {
	move({ 0, -10 * getSpeed() * deltaTime });
	return nullptr;
};