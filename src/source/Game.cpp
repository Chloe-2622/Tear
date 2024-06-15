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
	currentLevel.buildLevel(paterns, static_cast<float>(mWindow.getSize().x), static_cast<float>(mWindow.getSize().y));

	// Apply the view
	mWindow.setView(currentLevel.initView(static_cast<float>(mWindow.getSize().x), static_cast<float>(mWindow.getSize().y)));

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
			update(TimePerFrame);
		}

		mWindow.clear(sf::Color::White);
		render();
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
		}
	}
}

void Game::update(sf::Time elapsedTime) {
	mWindow.setView(currentLevel.UpdateView(static_cast<double>(elapsedTime.asMilliseconds())));
	currentLevel.Update(static_cast<double>(elapsedTime.asMilliseconds()), static_cast<float>(mWindow.getSize().y));
}

void Game::render() {
	currentLevel.Render(mWindow);
}