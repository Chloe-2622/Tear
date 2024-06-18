#include "Guided_Projectile.h"

Guided_Projectile::Guided_Projectile() : Projectile() {}

Guided_Projectile::Guided_Projectile(Transform const& transform, double speed, std::string const& texturePath) 
: Projectile(transform, speed, texturePath) 
{}

void Guided_Projectile::doDamage(GameObject & gameObject, double playerMultiplier) const {
    gameObject.takeDamage(playerMultiplier);
}