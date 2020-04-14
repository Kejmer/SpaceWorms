#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "hitbox.h"

// Forward declaration
class World;

class Entity {
public:
    enum CollisionCategory {
        Bullet,
        Hole,
        Spaceship,
        None
    };
    
    Entity(sf::Vector2f position, CollisionCategory category = None);
    virtual void input(sf::Event event) = 0;
    virtual void update(sf::Time dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();

    virtual void setWorld(World *world);
    World* getWorld();

    CollisionCategory getCategory() const;
    void setCategory(CollisionCategory category);

    bool doesCollide(Entity &entity);

    virtual sf::Transform getTransform() const;
protected:
    CollisionCategory collision_category;

    float distanceTo(sf::Vector2f where);
    sf::Vector2f position;
    World* world;

    std::unique_ptr<Hitbox> hitbox;
};

#endif
