#include "Game.hpp"
#include "Tear.h"

const sf::Time Game::TimePerFrame = sf::seconds(1.f / 60.f);

Game::Game() {}


void Game::initPaterns() {}


void Game::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	//GameObject player{Transform{{100, 100}, {50, 50}, 0}, 100, "resources/Shopkeeper_big.png"};
	Tear tear{ Transform{{100, 100}, {50, 50}, 0}, 100, "resources/Shopkeeper.png", 0, 0, 0, 0 };
	Player player{Transform{{100, 100}, {50, 50}, 0}, 100};

	// mWindow.setVerticalSyncEnabled(true);
	mWindow.setFramerateLimit(60);
	while (mWindow.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;
		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			tear.update(TimePerFrame.asMilliseconds());
			tear.render(mWindow);
			player.update(TimePerFrame.asMilliseconds());

			processEvents();
			update(TimePerFrame);
		}

		render();
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

void Game::update(sf::Time elapsedTime)
{
}

void Game::render()
{
	
}