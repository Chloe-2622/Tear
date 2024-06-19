#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>

class Player;
class Game;

enum Upgrade {
    HEALTH,
    SPEED,
    DAMAGE,
    GOLDMULTIPLIER,
    PROJECTILEDUPLICATION
};

class Shop {
    public:
        Shop();
        Shop(Game* game);


        //void Update();
        void Render(sf::RenderWindow& window) const;

        void Update();

        void handleInput(sf::Keyboard::Key key, bool isPressed);

    private:
        void upgrade(Upgrade upgrade);


        void resumeGame();


        // Player reference
        Player* player;
        Game *game;
};