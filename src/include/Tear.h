#include "GameObject.h"



class Tear : public GameObject {
public:
	explicit Tear();
	explicit Tear(Transform const& transform, double speed, std::string const& texturePath, int healthPoints, double scrollingPenalty, double damage, int goldreward);


	void		doDamage();
	bool		takeDamage();
	double		exitScreen();

private:
	int			healthPoints;
	double		scrollingPenalty;
	double		damage;
	int			goldReward;
};