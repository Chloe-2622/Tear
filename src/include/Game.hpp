#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Level.h"

class Game {
    public:
        explicit Game() = default;
        void                                    run();

    private:
        void                                    initPaterns();
        void                                    processEvents();
        void                                    update(sf::Time elapsedTime);
        void                                    render();
        void                                    handlePlayerInput(sf::Keyboard::Key key, bool isPressed);

        sf::RenderWindow                        mWindow{ sf::VideoMode{720, 1080}, "SFML Application", sf::Style::Close };
        static const sf::Time                   TimePerFrame;

        std::vector<std::unique_ptr<Patern>>    paterns;
        int                                     levelNumber;
        Level                                   currentLevel{ 0 };
};