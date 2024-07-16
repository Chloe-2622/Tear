#include "GameObjects/Projectiles/Projectile.h"

using namespace std;

// Constructeur
Projectile::Projectile(Transform const& transform, double speed, std::string const& texturePath, double damage) : 
    GameObject{transform, speed, texturePath, Faction::ALLY},
    damage{ damage }
{}

// Out of view
#pragma region Out of View
bool Projectile::isOutRenderZone(sf::View const& view, Vector2 windowSize) const {
    return getPosition().y < view.getCenter().y - windowSize.y/2 - getSize().y;
}
#pragma endregion Out of View

// Damages
#pragma region Collision
bool Projectile::onCollissionAction(GameObject& gameObject, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) {
	return gameObject.onCollisionActionReaction(Action::DAMAGE, damage * playerModifiersValue.damageMultiplier, playerModifiersValue, levelUpdateValues);
}

bool Projectile::onCollisionActionReaction(Action action, double actionValue, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) {
	return false;
}
#pragma endregion Collision

// Setter
void Projectile::setDamage(double newDamage) { damage = newDamage; }

// Debug
std::string Projectile::dump(std::string const& indent) const {
	ostringstream oss;
	oss << "Projectile" << endl;
	return oss.str();
}
