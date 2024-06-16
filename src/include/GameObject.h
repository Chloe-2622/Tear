#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include <string>
#include <vector>

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
        GameObject(Transform transform, double speed, std::string texturePath);

        GameObject(GameObject const& gameObject);

        void            Update(double deltaTime);
        void            Render(sf::RenderWindow &window) const;

        void            move(Vector2 movement);
        virtual bool    isOutofView(float const viewBottomBoarder) const = 0;
        virtual double  exitView() const;

        std::string     dump(std::string const& indent = "") const;

        Vector2         getPosition() const;
        Vector2         getSize() const;
        double          getRotation() const;


    protected:
        Transform       transform;
        double          speed;
        std::string     texturePath;

};