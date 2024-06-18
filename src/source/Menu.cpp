#include "Menu.h"
#include "Game.hpp"

Menu::Menu()
{
}

Menu::Menu(Game *game)
{
    this->game = game;
}

void Menu::Update(double deltaTime)
{
    blinkTime += deltaTime;

    if (blinkTime >= blinkInterval)
    {
        showBlinkText = !showBlinkText;
        blinkTime = 0;
    }
}

void Menu::Render(sf::RenderWindow& window) const
{
    // Menu Background
    sf::Texture menuBackgroundTexture;
    menuBackgroundTexture.loadFromFile("resources/Sprites/Menu/Menu.png");

    sf::Sprite menuBackground;
    menuBackground.setTexture(menuBackgroundTexture);

    window.draw(menuBackground);

    // Blink text
    if (showBlinkText)
    {
        sf::Texture blinkTexture;
        blinkTexture.loadFromFile("resources/Sprites/Menu/Press_Enter.png");

        sf::Sprite blinkSprite;
        blinkSprite.setTexture(blinkTexture);

        window.draw(blinkSprite);
    }

}

void Menu::handleInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::Key::Enter && isPressed)
    {
        startGame();
    }
}

void Menu::startGame()
{
    game->changeState(GameState::GAME);
}