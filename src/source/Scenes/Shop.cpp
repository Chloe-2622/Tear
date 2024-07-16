#include "Game.hpp"
#include "Scenes/Shop.h"

Shop::Shop(Game* game, Player* player) :
    Scene(game, "resources/Sprites/Shop/Shop.png"),
    player{ player }
{}

// Render
void Shop::Render(sf::RenderWindow& window) const
{
    Scene::Render(window);

    
}

// Inputs
void Shop::handleInput(sf::Keyboard::Key key, bool isPressed)
{
    if (key == sf::Keyboard::Key::Enter && isPressed)
    {
        resumeGame();
    }
}

void Shop::resumeGame() const {
    getGame()->changeState(GameState::GAME);
}