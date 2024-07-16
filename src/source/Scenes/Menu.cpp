#include "Game.hpp"
#include "Scenes/Menu.h"

Menu::Menu(Game* game) :
    Scene(game, "resources/Sprites/Menu/Menu.png")
{}

sf::View Menu::Update(double deltaTime)
{
    blinkTime += deltaTime;

    if (blinkTime >= blinkInterval)
    {
        showBlinkText = !showBlinkText;
        blinkTime = 0;
    }
    return Scene::Update(deltaTime);
}

void Menu::Render(sf::RenderWindow& window) const
{
    Scene::Render(window);

    // Blink text
    if (showBlinkText)
    {
        sf::Texture blinkTexture;
        blinkTexture = ResourceManager::getTexture(pessEnterPath);

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
    getGame()->changeState(GameState::GAME);
}