#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"

struct Vector2 {
    double x;
    double y;
};

struct Transform {
    Vector2 position;
    Vector2 size;
    double rotation;
};

class GameObject {
    public:
        GameObject();
        GameObject(Transform transform, double speed);        
        virtual void update(double deltaTime) = 0;
        virtual void render(sf::RenderWindow &window) = 0;
    protected:
        Transform transform;
        double speed;
        std::string texturePath;

};