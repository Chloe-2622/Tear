#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Player.h"

class Game {
    public:
        Game();
        void run();
    private:
        void processEvents();
        void update(sf::Time elapsedTime);
        void render();
        void handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

        sf::RenderWindow mWindow{sf::VideoMode{640, 480}, "SFML Application", sf::Style::Close};
        static const sf::Time TimePerFrame;

        std::unique_ptr<GameObject*> gameObjects;
};