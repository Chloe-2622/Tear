#include "Guided_Tear.h"

using namespace std;

#pragma region Constructeurs
Guided_Tear::Guided_Tear() :
	Tear()
{}

Guided_Tear::Guided_Tear(Transform const& transform, double speed, string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldReward) :
	Tear(transform, speed, texturePath, healthPoints, scrollingPenalty, damage, goldReward)
{}

Guided_Tear::Guided_Tear(const pugi::xml_node& node, Player player) :
	Tear(node)
{}

Guided_Tear::Guided_Tear(Guided_Tear const& guided_Tear) :
	Tear(guided_Tear)
{}
#pragma endregion Constructeurs

std::unique_ptr<Tear> Guided_Tear::copy() const {
	return make_unique<Guided_Tear>(*this);
}

//void Guided_Tear::Update() {};

