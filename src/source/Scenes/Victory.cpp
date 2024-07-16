#include "Scenes/Victory.h"

Victory::Victory(Game* game) :
	Scene(game, "resources/Sprites/Victory.png")
{}


void Render(sf::RenderWindow& window) const {
	Scene::Render(window);

	sf::Texture victoryTextTexture;
	victoryTextTexture = ResourceManager::getTexture("resources/Sprites/Press_Space.png");

	sf::Sprite victoryTextSprite;
	victoryTextSprite.setTexture(victoryTextTexture);

	victoryTextSprite.setPosition(window.getView().getCenter() - window.getView().getSize() / 2.f);

	mWindow.draw(victoryTextSprite);
}

void handleInput(sf::Keyboard::Key key, bool isPressed) override;
