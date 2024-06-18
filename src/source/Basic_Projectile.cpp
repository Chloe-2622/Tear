#include "Basic_Projectile.h"

Basic_Projectile::Basic_Projectile() : Projectile() {}

Basic_Projectile::Basic_Projectile(Transform const &transform, double speed, std::string const &texturePath) 
: Projectile(transform, speed, texturePath) 
{}