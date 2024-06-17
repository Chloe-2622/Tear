#include "vector"
#include "Tear.h"
#include "Patern.h"

class Level {
public:
	explicit Level(int levelNumber);
	Level() = default;

	sf::View										initView(float const windowWidth, float const windowLenght);
	void											buildLevel(std::vector<std::unique_ptr<Patern>> const& paterns, float const windowWidth, float const windowLenght);

	sf::View										UpdateView(double deltaTime);
	void											Update(double deltaTime, float const windowLenght);
	void											Render(sf::RenderWindow& window) const;

private:
	void											spawnPatern(Patern const& patern, Vector2 const& offset);
	void 										    spawnPlayer(float const windowWidth, float const windowLenght);
	sf::View										view;

	double											lenght = 2*1080;
	double											scrollingSpeed = 1;
	bool											hasReachedEnd = false;
	std::vector<std::unique_ptr<GameObject>>		gameObjects;
	std::unique_ptr<Player>							player;
};