#include "Projectile.h"

using namespace std;

// Constructeur
Projectile::Projectile(Transform const& transform, double speed, std::string const& texturePath, double damage) : 
    GameObject{transform, speed, texturePath, Faction::Ally},
    damage{ damage }
{}

// Update
void Projectile::supressOffset(Vector2 offset) { move(offset); }

// Out of view
bool Projectile::isOutofView(sf::FloatRect currentViewBox) const { return getPosition().y < currentViewBox.top - getSize().y; }

// Damages
#pragma region Damages
bool Projectile::hasCollided(GameObject const& gameObject) const {
    return getPosition().distance(gameObject.getPosition()) < getSize().x;
}

bool Projectile::doDamage(GameObject& gameObject, double playerMultiplier) const {
    return gameObject.takeDamage(damage * playerMultiplier);
}

bool Projectile::takeDamage(double damages) { return false; }; // Un missile ne peut pas prendre de dégâts
#pragma endregion Damage

// Setter
void Projectile::setDamage(double newDamage) { damage = newDamage; }