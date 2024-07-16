#include "Scenes/Scene.h"
#include "Game.hpp"

using namespace std;

Scene::Scene(Game* game, string const& backgroundPath) :
	backgroundPath{ backgroundPath },
	game{ game }
{}

Scene::Scene(Game* game, string const& backgroundPath, std::string const& backgroundTextPath) :
	backgroundPath{ backgroundPath },
	backgroundTextPath{ backgroundTextPath },
	game{ game }
{}

// Update
sf::View Scene::Update(double deltaTime) {
	return view;
}

// Render
void Scene::Render(sf::RenderWindow& window) const {
	renderBackground(window);
}

void Scene::renderBackground(sf::RenderWindow& window) const {
	// Menu Background
	sf::Texture backgroundTexture;
	backgroundTexture.loadFromFile(backgroundPath);

	sf::Sprite background;
	background.setTexture(backgroundTexture);

	window.draw(background);

	if (backgroundTextPath != "") {
		sf::Texture menuTextTexture;
		menuTextTexture = ResourceManager::getTexture(backgroundTextPath);

		sf::Sprite menuTextSprite;
		menuTextSprite.setTexture(menuTextTexture);

		menuTextSprite.setPosition(window.getView().getCenter() - window.getView().getSize() / 2.f);

		window.draw(menuTextSprite);
	}
}

// Getter
sf::View Scene::getView() const { return view; }
Game* Scene::getGame() const { return game; }
std::string	Scene::getBackgroundPath() const { return backgroundPath; };
