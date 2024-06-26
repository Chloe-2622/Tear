#pragma once

#include "vector"
#include "Tear.h"
#include "Patern.h"
#include "Goal.h"
#include "Player.h"
#include "Projectile.h"
#include <SFML/Audio.hpp>
#include <memory>

class Level {
public:
	explicit Level(int levelNumber, Game* game);
	Level() = default;

	// Initialize the level
	sf::View										initView(float const windowWidth, float const windowLenght);
	void											buildLevel(std::vector<std::unique_ptr<Patern>> const& paterns);


	// Update the level
	sf::View										Update(double deltaTime);
	void											Render(sf::RenderWindow& window) const;
	void 											renderBackground(sf::RenderWindow& window) const;

	// Getter
	Player&											getPlayerPtr();


private:
	// Initialize the level
	void											spawnPatern(Patern const& patern, Vector2 const& offset);
	void 										    spawnPlayer();
	void											spawnGoal();


	// Update the level
	void											UpdateView(double deltaTime);


	// Parameters
	double											lenght = 2*1080;
	double											scrollingSpeed = 200;
	bool											hasReachedEnd = false;
	std::vector<std::unique_ptr<GameObject>>		gameObjects;
	std::vector<std::pair<int, int>> 				backgroundsPositions;

	std::unique_ptr<Player>							player;
	Vector2											windowSize;
	std::unique_ptr<Goal>							goal;
	sf::View										view;

	Game*											game;
};