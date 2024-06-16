#pragma once

#include "GameObject.h"



class Tear : public GameObject {
public:
	explicit Tear();
	explicit Tear(Transform const& transform, double speed, std::string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldreward);


	void		doDamage();
	bool		takeDamage();
	double		exitScreen();

	void update(double deltaTime) override {};
	void render(sf::RenderWindow& window) override {};

private:
	int			healthPoints;
	double		scrollingPenalty;
	double		damage;
	int			goldReward;
};