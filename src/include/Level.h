#include "vector"
#include "Tear.h"
#include "Patern.h"
#include "Goal.h"
#include "Player.h"
#include "Projectile.h"

class Level {
public:
	explicit Level(int levelNumber);
	Level() = default;

	sf::View										initView(float const windowWidth, float const windowLenght);
	void											buildLevel(std::vector<std::unique_ptr<Patern>> const& paterns);

	sf::View										UpdateView(double deltaTime);
	void											Update(double deltaTime);
	void											Render(sf::RenderWindow& window) const;
	void 											renderBackground(sf::RenderWindow& window) const;

	// Getter
	std::unique_ptr<Player> const&					getPlayer() const { return player; }

private:
	void											spawnPatern(Patern const& patern, Vector2 const& offset);
	void 										    spawnPlayer();
	void											spawnGoal();
	sf::View										view;

	double											lenght = 2*1080;
	double											scrollingSpeed = 200;
	bool											hasReachedEnd = false;
	std::vector<std::unique_ptr<GameObject>>		gameObjects;
	std::vector<std::unique_ptr<Projectile>>		projectiles;
	std::vector<std::pair<int, int>> 				backgroundsPositions;
	std::unique_ptr<Player>							player;
	Vector2											windowSize;
	std::unique_ptr<Goal>							goal;
};