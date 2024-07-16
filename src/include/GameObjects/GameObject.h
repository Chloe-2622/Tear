#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "pugixml.hpp"
#include "ResourceManager.h"

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

    bool operator==(const Transform& t) const = default;

};

struct PlayerModifiersValue {
    double damageMultiplier = 0;
    double goldMultiplier = 0;
};

enum class Faction {
    ALLY,
    ENEMIE,
    UPGRADE
};

enum class Action {
    NONE,
    DAMAGE,
    UPGRADE
};

struct LevelUpdateValues;

class GameObject {
    public:
                                /* Constructeurs */ 
        explicit GameObject() = default;
        virtual ~GameObject() = default;
        explicit GameObject(Transform const& transform, double speed, std::string const& texturePath, Faction faction);
        explicit GameObject(const pugi::xml_node& node, double speed, std::string const& texturePath, Faction faction);
        explicit GameObject(GameObject const& gameObject) = default;

                                /* Render */ 
        virtual void            Render(sf::RenderWindow &window) const;

                                /* Update */
        virtual void            Update(double deltaTime, sf::View const& view, Vector2 windowSize, Vector2 playerPosition, std::vector<std::unique_ptr<GameObject>>* gameObjects, LevelUpdateValues* levelUpdateValues);
        void                    followView(Vector2 movement);
        void                    move(Vector2 viewMovement);

                                /* Out of view */
        // Return true if the object quit its render zone
        virtual bool            isOutRenderZone(sf::View const& view, Vector2 windowSize) const = 0;
        // Actions to do when exiting render zone
        virtual void            exitRenderZone(LevelUpdateValues* levelUpdateValues);

                                /* Collision */
        // Check collision with a vector of gameObjects
        void                    handleCollisions(const std::vector<std::unique_ptr<GameObject>>* gameObjects, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues);
        // Check collision with one gameObject
        void                    handleCollision(GameObject& gameObject, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues);
        // Check if the collision has occured
        virtual bool            hasCollided(GameObject const& gameObject) const;

        // How to react when collision
        void                    onCollissionReaction(GameObject& gameObject, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues);
        
        // Action to do when collision, return true if action succeded
        virtual bool            onCollissionAction(GameObject& gameObject, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) = 0;
        // Reaction to the action of a collision, return true if action succeded
        virtual bool            onCollisionActionReaction(Action action, double actionValue, PlayerModifiersValue const playerModifiersValue, LevelUpdateValues* levelUpdateValues) = 0;

        // Operations
        bool                    operator==(const GameObject& g) const;

                                /* Getter */
        Vector2                 getPosition() const;
        Vector2                 getSize() const;
        double                  getRotation() const;
        double                  getSpeed() const;

                                /* Setter */
        void                    setPosition(Vector2 position);
        void                    setTexturePath(std::string_view const& newTexturePath);
        void                    setSpeed(double newSpeed);
        void                    setRotation(double newRotation);

        // Booleans
        void                    setFriendlyFire(bool newFriendlyFire);
        void                    setFollowingView(bool newFollowingView);
        void                    setDestroyOnHit(bool newDestroyOnHit);


        // Debug
        virtual std::string     dump(std::string const& indent = "") const;

    private:
        Transform               transform = { {0, 0}, {0, 0}, 0 };
        std::string             texturePath = "";
        double                  speed = 0;
        Faction                 faction = Faction::ALLY;

        // Booléens
        bool                    friendlyFire = false;
        bool                    followingView = false;
        bool                    destroyOnHit = false;
};

struct LevelUpdateValues {
    double scrollingPenalty = 0;
    int goldEarned = 0;
    std::vector<GameObject*> killedObjects;

    bool playerKilled = false;
};