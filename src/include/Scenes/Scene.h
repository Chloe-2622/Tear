#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "ResourceManager.h"
#include "Game.hpp"

class Scene {
public:
	explicit Scene(Game* game, string const& backgroundPath);
	explicit Scene(Game* game, std::string const& backgroundPath, std::string const& backgroundTextPath);
	Scene() = default;
	virtual ~Scene() = default;

	// Render
	virtual void						Render(sf::RenderWindow& window) const;
	virtual void						renderBackground(sf::RenderWindow& window) const;

	// Update
	virtual sf::View					Update(double deltaTime);

	// Inputs
	virtual void						handleInput(sf::Keyboard::Key key, bool isPressed) = 0;

	// Getter
	sf::View							getView() const;
	Game*								getGame() const;
	std::string							getBackgroundPath() const;

private:
	std::string							backgroundPath;
	std::string							backgroundTextPath = "";
	Game*								game;
	sf::View							view;
};