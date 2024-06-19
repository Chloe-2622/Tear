#pragma once

#include <SFML/Graphics.hpp>
#include "ResourceManager.h"
#include "pugixml.hpp"
#include <string>
#include <vector>

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
    void operator+=(const Vector2 v) { x += v.x; y += v.y; }
    Vector2 operator-(const Vector2 v) const { return { x - v.x, y - v.y }; }
    Vector2 operator*(const double k) const { return { k*x, k*y }; }
    bool operator==(const Vector2& v) const = default;

};

struct Transform {
    Vector2 position;
    Vector2 size;
    double rotation;
};

enum class Faction {
    Ally,
    Enemie
};




class GameObject {
    public:
        // Constructeurs
        explicit GameObject() = default;
        virtual ~GameObject() = default;
        explicit GameObject(Transform const& transform, double speed, std::string const& texturePath, Faction faction);
        explicit GameObject(const pugi::xml_node& node, double speed, std::string const& texturePath, Faction faction);
        explicit GameObject(GameObject const& gameObject) = default;

        // Render
        virtual void                                                Render(sf::RenderWindow &window) const;

        // Update
        virtual std::unique_ptr<GameObject>                         Update(double deltaTime, sf::View const& view, Vector2 windowSize, Vector2 playerPosition);
        virtual void                                                followView(Vector2 movement) = 0;
        virtual void                                                supressViewOffset(Vector2 offset) = 0;

        // Out of view
        virtual bool                                                isOutofView(sf::View const& view, Vector2 windowSize) const = 0;
        virtual double                                              exitViewValue() const;

        // Damages
        GameObject*                                                 hasHitSomething(const std::vector<std::unique_ptr<GameObject>>* gameObjects) const;
        virtual bool                                                hasHitObject(GameObject const& gameObject) const;
        virtual bool                                                hasCollided(GameObject const& gameObject) const = 0;
        virtual bool                                                doDamage(GameObject & gameObject, double playerMultiplier) const = 0; // True si kill
        virtual bool                                                takeDamage(double damages) = 0; // True si mort
        virtual int                                                 killReward(double playerMultiplier) const;

        // Getter
        Vector2                                                     getPosition() const;
        Vector2                                                     getSize() const;
        double                                                      getRotation() const;
        double                                                      getSpeed() const;
        bool                                                        isDestroyedOnHit() const;

        // Setter
        void                                                        setPosition(Vector2 position);
        void                                                        move(Vector2 movement);
        void                                                        setTexturePath(std::string_view const& newTexturePath);
        void                                                        setSpeed(double newSpeed);
        void                                                        setRotation(double newRotation);            
        void                                                        setIsDestroyedOnHit(bool newDestroyOnHit);


        // Debug
        virtual std::string                                         dump(std::string const& indent = "") const;

    private:
        Transform                                                   transform = { {0, 0}, {0, 0}, 0 };
        std::string                                                 texturePath = "";
        double                                                      speed = 0;
        Faction                                                     faction = Faction::Ally;
        bool                                                        destroyOnHit = false;
};