#include "Projectile.h"

using namespace std;

// Constructeur
Projectile::Projectile(Transform const& transform, double speed, std::string const& texturePath, double damage) : 
    GameObject{transform, speed, texturePath, Faction::Ally},
    damage{ damage }
{
	setIsDestroyedOnHit(true);
}

// Update
void Projectile::followView(Vector2 movement) { move(movement); }
void Projectile::supressViewOffset(Vector2 offset) { move(offset); }

// Out of view
bool Projectile::isOutofView(sf::View const& view, Vector2 windowSize) const { 
    return getPosition().y < view.getCenter().y - windowSize.y/2 - getSize().y;
}

// Damages
#pragma region Damages
bool Projectile::hasCollided(GameObject const& gameObject) const {
	// Same line on X
	if (gameObject.getPosition().x < getPosition().x + getSize().x && gameObject.getPosition().x + gameObject.getSize().x > getPosition().x) {

		// Same column on Y 
		return gameObject.getPosition().y < getPosition().y + getSize().y && gameObject.getPosition().y + gameObject.getSize().y > getPosition().y;
	}
	return false;
}

bool Projectile::doDamage(GameObject& gameObject, double playerMultiplier) const {
    return gameObject.takeDamage(damage * playerMultiplier);
}

bool Projectile::takeDamage(double damages) { return false; }; // Une missile ne prends pas de dégâts
#pragma endregion Damage

// Setter
void Projectile::setDamage(double newDamage) { damage = newDamage; }

// Debug
std::string Projectile::dump(std::string const& indent) const {
	ostringstream oss;
	oss << "Projectile" << endl;
	return oss.str();
}
