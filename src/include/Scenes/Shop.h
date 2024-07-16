#pragma once

#include <iostream>
#include "Scenes/Scene.h"
#include "GameObjects/Player.h"

enum class Upgrade {
    HEALTH,
    SPEED,
    DAMAGE,
    GOLDMULTIPLIER,
    PROJECTILEDUPLICATION
};

class Shop : public Scene {
    public:
        explicit Shop(Game* game, Player* player);
        ~Shop() override = default;

        // Render
        void Render(sf::RenderWindow& window) const override;

        sf::View Update(double deltaTime) override;

        void handleInput(sf::Keyboard::Key key, bool isPressed) override;

    private:
        void resumeGame() const;

        // Player reference
        Player* player;
};