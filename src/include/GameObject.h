#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include <string>
#include <vector>

class Player;

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
        // Constructeurs
        GameObject();
        virtual ~GameObject() = default;
        GameObject(Transform const& transform, double speed, std::string const& texturePath);
        GameObject(GameObject const& gameObject);

        // Update & Render
        virtual void    Update(double deltaTime);
        void            Render(sf::RenderWindow &window) const;

        virtual bool    isOutofView(float const viewBottomBoarder) const;
        virtual double  exitView() const;

        virtual bool    hit(Player const& player, std::vector<std::unique_ptr<GameObject>> const& gameObjects) const;
        virtual void    doDamage(GameObject gameObject, double playerMultiplier) const;
        virtual bool    takeDamage(double damages);


        void            move(Vector2 movement);

        // Getter
        Vector2         getPosition() const;
        Vector2         getSize() const;
        double          getRotation() const;

        // Debug
        std::string     dump(std::string const& indent = "") const;

    private:
        Transform       transform;
        double          speed;
        std::string     texturePath;
};