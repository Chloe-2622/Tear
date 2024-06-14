#include "vector"
#include "Tear.h"
#include "Game.hpp"

class Level {
public:
	explicit Level(int levelNumber);

	void buildLevel(std::vector<Patern> const& parterns);
	void Update(double deltaTime);
	void Render(sf::RenderWindow& window);

private:
	double		lenght = 2000;
	double		scrollingSpeed = 0;
	std::vector<std::unique_ptr<GameObject>> gameObjects;
};