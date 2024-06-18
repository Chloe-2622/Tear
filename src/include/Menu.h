#pragma once

#include <SFML/Graphics.hpp>

class Game;

class Menu 
{
public:
    Menu();
    Menu(Game *game);

    void Update(double deltaTime);
    void Render(sf::RenderWindow& window) const;

    void handleInput(sf::Keyboard::Key key, bool isPressed);
private:
    void startGame();

    bool isGameRunning = false;

    double blinkInterval = 0.5;
    double blinkTime = 0;
    bool showBlinkText = true;

    Game *game;
};