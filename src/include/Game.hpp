#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "GameObjects/GameObject.h"
#include "Scenes/Scene.h"   
#include "Patern.h"

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

        void                                    changeState(GameState state);

    private:
        // Initialize
        void                                    initPaterns();

        // Runtime
        void                                    processEvents();
        void                                    handleInput(sf::Keyboard::Key key, bool isPressed);

        // Update
        void                                    Update(sf::Time elapsedTime);

        // Render
        void                                    Render();        

        // Parameters
        sf::RenderWindow                        mWindow{ sf::VideoMode{720, 1080}, "SFML Application", sf::Style::Close };
        static const sf::Time                   TimePerFrame;

        std::vector<std::unique_ptr<Patern>>    paterns;
        int                                     levelNumber{-1};
        std::unique_ptr<Scene>                  scene;

        GameState                               gameState = GameState::MENU;

};