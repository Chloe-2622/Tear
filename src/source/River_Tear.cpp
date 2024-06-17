#include "River_Tear.h"

using namespace std;

#pragma region Constructeurs
River_Tear::River_Tear() :
	Tear()
{
	setScrollingPenalty(0);
}

River_Tear::River_Tear(Transform const& transform, double speed, string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldReward) :
	Tear(transform, speed, texturePath, healthPoints, scrollingPenalty, damage, goldReward)
{
	setScrollingPenalty(0);
}

River_Tear::River_Tear(const pugi::xml_node& node) :
	Tear(node)
{
	setScrollingPenalty(0);
}

River_Tear::River_Tear(River_Tear const& guided_Tear) :
	Tear(guided_Tear)
{}
#pragma endregion Constructeurs

std::unique_ptr<Tear> River_Tear::copy() const {
	return make_unique<River_Tear>(*this);
}

void River_Tear::Update(double deltaTime, double scrollingSpeed, float viewPositionY, float windowLenght, Vector2 playerPosition) {
}