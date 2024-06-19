#include "Shop.h"
#include "Game.hpp"

Shop::Shop()
{
}

Shop::Shop(Game* game)
{
    this->game = game;
}

void Shop::Update()
{
}

void Shop::Render(sf::RenderWindow& window) const
{
    
    
    // Menu Background
    sf::Texture menuBackgroundTexture;
    menuBackgroundTexture.loadFromFile("resources/Sprites/Shop/Shop.png");

    sf::Sprite menuBackground;
    menuBackground.setTexture(menuBackgroundTexture);

    window.draw(menuBackground);
    
    sf::Texture menuTextTexture;
    menuTextTexture.loadFromFile("resources/Sprites/Press_Enter_Continue.png");

    sf::Sprite menuTextSprite;
    menuTextSprite.setTexture(menuTextTexture);

    menuTextSprite.setPosition(window.getView().getCenter() - window.getView().getSize() / 2.f);

    window.draw(menuTextSprite);
}

void Shop::upgrade(Upgrade upgrade)
{
}

void Shop::handleInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::Key::Enter && isPressed)
    {
        resumeGame();
    }
}

void Shop::resumeGame()
{
    game->changeState(GameState::GAME);
}