#pragma once

#include "GameObject.h"
#include "pugixml.hpp"
#include "Player.h"


class Tear : public GameObject {
public:
	// Constructeurs
	explicit Tear();
	~Tear() override = default;
	explicit Tear(Transform const& transform, double speed, std::string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldreward);
	explicit Tear(const pugi::xml_node& node);
	explicit Tear(Tear const& tear);

	// Construct Level
	virtual std::unique_ptr<Tear> copy() const;

	void		doDamage(GameObject gameObject, double playerMultiplier) const override;
	bool		takeDamage(double damages) override;

	// Test eaxh frames
	bool		isOutofView(float const viewBottomBoarder) const override;
	double		exitView() const override; // Result if true
	bool		hit(Player const& player, std::vector<std::unique_ptr<GameObject>> const& gameObjects) const override;
	
private:
	int			healthPoints = 100;
	double		scrollingPenalty = 1;
	double		damage = 10;
	int			goldReward = 10;
};