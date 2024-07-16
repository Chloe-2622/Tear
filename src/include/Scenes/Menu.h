#pragma once

#include "Scenes/Scene.h"

class Game;

class Menu : public Scene {
public:
    explicit Menu(Game* game);
    ~Menu() override = default;

    // Render
    void Render(sf::RenderWindow& window) const override;

    sf::View Update(double deltaTime) override;

    void handleInput(sf::Keyboard::Key key, bool isPressed) override;

private:
    void startGame();

    bool isGameRunning = false;
    std::string pessEnterPath = "resources/Sprites/Menu/Press_Enter.png";

    double blinkInterval = 0.5;
    double blinkTime = 0;
    bool showBlinkText = true;
};