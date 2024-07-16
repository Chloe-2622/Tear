#include <iostream>
#include <string>
#include "Game.hpp"


using namespace std;

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

void Game::initPaterns() {
	pugi::xml_document doc;

	if (auto result = doc.load_file("resources/Paterns.xml"); !result)
	{
		cerr << "Could not open file Paterns.xml because " << result.description() << endl;
		return;
	}

	for (pugi::xml_node patern : doc.child("Paterns").children()) {
		paterns.push_back(make_unique<Patern>(patern));
	}

	for (auto const& patern : paterns) {
		cout << patern->dump();
	}
}

void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;


	initPaterns();

	// Apply the view
	//currentLevel.buildLevel(paterns);

	// mWindow.setVerticalSyncEnabled(true);
	mWindow.setFramerateLimit(60);
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;

			processEvents();
			Update(TimePerFrame);
		}

		mWindow.clear(sf::Color::Black);
		Render();
		mWindow.display();
	}
}

void Game::processEvents()
{
	sf::Event event{sf::Event::Count}; // Initialization to an impossible value (in order to suppress Clang-Tidy warning)
	while (mWindow.pollEvent(event))
	{
		switch (event.type)
		{
			case sf::Event::Closed:
				mWindow.close();
				break;
			case sf::Event::KeyPressed:
				scene->handleInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				scene->handleInput(event.key.code, false);
				break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
	currentLevel.getPlayerPtr().handleInput(key, isPressed);
}

void Game::handleMenuInput(sf::Keyboard::Key key, bool isPressed) {
	menu.handleInput(key, isPressed);
}

void Game::handleShopInput(sf::Keyboard::Key key, bool isPressed) {
	shop.handleInput(key, isPressed);
}

void Game::handleVictoryInput(sf::Keyboard::Key key, bool isPressed) {
	if (key == sf::Keyboard::Space) {
		changeState(SHOP);
	}
}

void Game::handleGameoverInput(sf::Keyboard::Key key, bool isPressed) {
	if (key == sf::Keyboard::Space) {
		changeState(MENU);
	}
}

void Game::Update(sf::Time elapsedTime) {
	switch (gameState) {
		case MENU:
			menu.Update(static_cast<double>(elapsedTime.asSeconds()));
			break;
		case GAME:
			UpdateLevel(elapsedTime);
			break;
		case PAUSE:
			break;
		case VICTORY:
			break;
		case GAMEOVER:
			break;
		case SHOP:
			//shop.Update();
			break;
	}
}

void Game::UpdateLevel(sf::Time elapsedTime) {
	sf::View newView = currentLevel.Update(static_cast<double>(elapsedTime.asSeconds()));
	if (gameState == GAME) mWindow.setView(newView);
	std::cout << "Changing view center to : " << mWindow.getView().getCenter().x << ", " << mWindow.getView().getCenter().y << std::endl;
}

void Game::changeState(GameState state) {
	GameState oldGameState = gameState;

	if ((oldGameState == MENU || oldGameState == SHOP) && state == GAME) {
		levelNumber++;
		currentLevel = Level(levelNumber, this);
		mWindow.setView(currentLevel.initView(static_cast<float>(mWindow.getSize().x), static_cast<float>(mWindow.getSize().y)));
		
		currentLevel.buildLevel(paterns);
	}
	if (state == SHOP) {
		std::cout << "Shop" << std::endl;
		mWindow.setView(sf::View(sf::FloatRect(0, 0, static_cast<float>(mWindow.getSize().x), static_cast<float>(mWindow.getSize().y))));
		std::cout << "View center : " << mWindow.getView().getCenter().x << ", " << mWindow.getView().getCenter().y << std::endl;
	}
	if (state == GAMEOVER) {
		levelNumber = -1;
	}

	gameState = state;
}

void Game::Render() {
	switch (gameState) {
		case MENU:
			RenderMenu();
			break;
		case GAME:
			currentLevel.Render(mWindow);
			break;
		case PAUSE:
			currentLevel.Render(mWindow);
			RenderPause();
			break;
		case VICTORY:
			currentLevel.Render(mWindow);
			RenderVictory();
			break;
		case GAMEOVER:
			currentLevel.Render(mWindow);
			RenderGameover();
			break;
		case SHOP:
			RenderShop();
			break;
	}
}

void Game::RenderMenu() {
	menu.Render(mWindow);
}

void Game::RenderPause() {
}



void Game::RenderGameover() {
	sf::Texture gameoverTexture;
	gameoverTexture = ResourceManager::getTexture("resources/Sprites/Press_Space_Restart.png");

	sf::Sprite gameoverSprite;
	gameoverSprite.setTexture(gameoverTexture);

	mWindow.draw(gameoverSprite);

	sf::Texture gameoverTextTexture;
	gameoverTextTexture = ResourceManager::getTexture("resources/Sprites/Press_Space_Restart.png");

	sf::Sprite gameoverTextSprite;
	gameoverTextSprite.setTexture(gameoverTextTexture);

	gameoverTextSprite.setPosition(mWindow.getView().getCenter() - mWindow.getView().getSize() / 2.f);

	mWindow.draw(gameoverTextSprite);
}

void Game::RenderShop() {
	shop.Render(mWindow);
}