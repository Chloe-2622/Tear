#include "Game.hpp"

#include "iostream"
#include <string>


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
	mWindow.setView(currentLevel.initView(static_cast<float>(mWindow.getSize().x), static_cast<float>(mWindow.getSize().y)));
	currentLevel.buildLevel(paterns);

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
				handlePlayerInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				handlePlayerInput(event.key.code, false);
				break;
		}
	}
}

void Game::handlePlayerInput(sf::Keyboard::Key key, bool isPressed) {
	currentLevel.getPlayerPtr().handleInput(key, isPressed);
}

void Game::Update(sf::Time elapsedTime) {
	mWindow.setView(currentLevel.Update(static_cast<double>(elapsedTime.asSeconds())));
}

void Game::Render() {
	currentLevel.Render(mWindow);
}