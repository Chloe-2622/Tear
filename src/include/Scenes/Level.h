#pragma once

#include <vector>
#include <SFML/Audio.hpp>
#include <memory>
#include "Scenes/Scene.h"
#include "GameObjects/Player.h"
#include "GameObjects/Tears/Tear.h"
#include "Patern.h"
#include "Goal.h"

class Level : public Scene {
public:
	explicit Level(Game* game, int levelNumber);
	explicit Level(Game* game, int levelNumber, Player* player);
	~Level() override = default;
	Level() = default;

	// Render
	void											Render(sf::RenderWindow& window) const override;
	void											renderBackground(sf::RenderWindow& window) const override;

	// Update
	sf::View										Update(double deltaTime) override;

	// Inputs
	void											handleInput(sf::Keyboard::Key key, bool isPressed) override;

	// Initialize the level
	sf::View										initView(float const windowWidth, float const windowLenght);
	void											buildLevel(std::vector<std::unique_ptr<Patern>> const& paterns);

	// Getter
	std::unique_ptr<Player>							getPlayerPtr();

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

	Vector2											windowSize;
	std::unique_ptr<Goal>							goal;
	sf::View										view;

	std::unique_ptr<Player>							player;
	Game*											game;
};