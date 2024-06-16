#pragma once

#include "GameObject.h"
#include "pugixml.hpp"


class Tear : public GameObject {
public:
	explicit Tear();
	explicit Tear(Transform const& transform, double speed, std::string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldreward);
	explicit Tear(const pugi::xml_node& node);
	explicit Tear(Tear const& tear);

	bool		isOutofView(float const viewBottomBoarder) const override;
	double		exitView() const override;

	std::unique_ptr<Tear> copy() const;

	void		doDamage();
	bool		takeDamage();
	double		exitScreen();

	void 		Update(double deltaTime) override;

private:
	int			healthPoints;
	double		scrollingPenalty;
	double		damage;
	int			goldReward;
};