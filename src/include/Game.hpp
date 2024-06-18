#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Level.h"

enum GameState {
    MENU,
    GAME,
    PAUSE,
    VICTORY,
    GAMEOVER,
    SHOP
};


class Game {
    public:
        explicit Game() = default;
        void                                    run();

    private:
        // Initialize
        void                                    initPaterns();

        // Runtime
        void                                    processEvents();
        void                                    handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
        void                                    Update(sf::Time elapsedTime);
        void                                    Render();

        // Parameters
        sf::RenderWindow                        mWindow{ sf::VideoMode{720, 1080}, "SFML Application", sf::Style::Close };
        static const sf::Time                   TimePerFrame;

        std::vector<std::unique_ptr<Patern>>    paterns;
        int                                     levelNumber;
        Level                                   currentLevel{ 0 };

        GameState                               gameState = MENU;
};