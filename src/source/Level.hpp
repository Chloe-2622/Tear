#include "Level.h"

Level::Level(int levelNumber)
{
	for (int i = 0; i < levelNumber; i++) {
		baseLenght += lenght * 10/100
	}
	lenght = baseLenght;
}

void Level::buildLevel(std::vector<Patern> const& parterns) {

}

void Level::Update(double deltaTime) {
	for (GameObject gameObject : gameObjects) {
		gameObject.Update(deltaTime);
	}
}

void Level::Render(sf::RenderWindow& window) {
	for (GameObject gameObject : gameObjects) {
		gameObject.Render(window);
	}
}

