#pragma once

#include <iostream>
#include "Scenes/Scene.h"

class Victory : public Scene {
public:
    explicit Victory(Game* game);
    ~Victory() override = default;

    // Render
    void Render(sf::RenderWindow& window) const override;

    // Handle input
    void handleInput(sf::Keyboard::Key key, bool isPressed) override;
};