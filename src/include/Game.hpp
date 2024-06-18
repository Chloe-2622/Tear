#pragma once

#include <SFML/Graphics.hpp>
#include "GameObject.h"
#include "Patern.h"
#include "Menu.h"
#include "Shop.h"
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

        void                                    changeState(GameState state);

    private:
        // Initialize
        void                                    initPaterns();

        // Runtime
        void                                    processEvents();
        void                                    handlePlayerInput(sf::Keyboard::Key key, bool isPressed);
        void                                    handleMenuInput(sf::Keyboard::Key key, bool isPressed);
        void                                    handleShopInput(sf::Keyboard::Key key, bool isPressed);
        void                                    Update(sf::Time elapsedTime);
        void                                    UpdateLevel(sf::Time elapsedTime);
        void                                    Render();
        void                                    RenderMenu();
        void                                    RenderPause();
        void                                    RenderVictory();
        void                                    RenderGameover();
        void                                    RenderShop();

        

        // Parameters
        sf::RenderWindow                        mWindow{ sf::VideoMode{720, 1080}, "SFML Application", sf::Style::Close };
        static const sf::Time                   TimePerFrame;

        std::vector<std::unique_ptr<Patern>>    paterns;
        int                                     levelNumber{-1};
        Level                                   currentLevel{ 0, this };

        Menu                                    menu{this};
        Shop                                    shop{this};

        GameState                               gameState = MENU;

};