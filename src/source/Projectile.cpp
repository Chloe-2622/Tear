#include "Projectile.h"

Projectile::Projectile(Transform const& transform, double speed, std::string const& texturePath) : GameObject(transform, speed, texturePath) {}

void Projectile::UpdateProjectile(double deltaTime, float viewPositionY, float windowLength, float windowWidth) {
    move({0, -10*getSpeed()*deltaTime});
}

bool Projectile::isOutofView(sf::FloatRect currentViewBox) const {
    return getPosition().y < currentViewBox.top - getSize().y;
}

bool Projectile::takeDamage(double damages) { return false; }