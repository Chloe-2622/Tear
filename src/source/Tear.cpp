#include "Tear.h"

using namespace std;


Tear::Tear() :
	GameObject(),
	healthPoints{ 0 },
	scrollingPenalty{ 0 },
	damage{ 0 },
	goldReward{ 0 }
{}

Tear::Tear(Transform const& transform, double speed, string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldReward):
	GameObject(transform, speed, texturePath),
	healthPoints{ healthPoints },
	scrollingPenalty{ scrollingPenalty },
	damage{ damage },
	goldReward{ goldReward }
{}

void Tear::doDamage() {}
bool Tear::takeDamage() { return false; }
double Tear::exitScreen() { return 0; }