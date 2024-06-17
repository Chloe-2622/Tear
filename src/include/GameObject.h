#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "pugixml.hpp"
#include <string>
#include <vector>

class Player;

struct Vector2 {
    double x;
    double y;

    void normalize() {
        x = x / sqrt(pow(x, 2) + pow(y, 2));
        y = y / sqrt(pow(x, 2) + pow(y, 2));
    }

    double distance(Vector2 v) const {
        return sqrt(pow(v.x - x, 2) + pow(v.y - y, 2));
    }

    Vector2 operator+(const Vector2 v) const { return { x + v.x, y + v.y }; }
    Vector2 operator-(const Vector2 v) const { return { x - v.x, y - v.y }; }
    Vector2 operator*(const double k) const { return { k*x, k*y }; }
};

struct Transform {
    Vector2 position;
    Vector2 size;
    double rotation;
};

class GameObject {
    public:
        // Constructeurs
        explicit GameObject();
        virtual ~GameObject() = default;
        explicit GameObject(Transform const& transform, double speed, std::string const& texturePath);
        explicit GameObject(const pugi::xml_node& node, double speed, std::string texturePath);
        explicit GameObject(GameObject const& gameObject);

        // Update & Render
        virtual void            Update(double deltaTime, double scrollingSpeed = 0, float viewPositionY = 0, float windowLenght = 0, Vector2 playerPosition = {0, 0});
        void                    Render(sf::RenderWindow &window) const;

        virtual bool            isOutofView(sf::FloatRect currentViewBox) const;
        virtual double          exitView() const;

        virtual void hit(Player & player, std::vector<std::unique_ptr<GameObject>> const& gameObjects) const = 0;
        virtual void            doDamage(GameObject & gameObject, double playerMultiplier) const = 0;
        virtual bool            takeDamage(double damages) = 0;


        void            move(Vector2 movement);

        // Getter
        Vector2         getPosition() const;
        Vector2         getSize() const;
        double          getRotation() const;
        double          getSpeed() const;

        // Setter
        void            setPosition(Vector2 position) {transform.position = position;};

        // Debug
        std::string     dump(std::string const& indent = "") const;
    private:
        Transform       transform;
        double          speed;
        std::string     texturePath;
};