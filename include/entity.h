#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

// Forward declaration
class World;

class Entity {
public:
    Entity(sf::Vector2f position);
    virtual void input(sf::Event event) = 0;
    virtual void update(sf::Time dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();

    virtual void setWorld(World *world);
    World* getWorld();
protected:
    float distanceTo(sf::Vector2f where);
    sf::Vector2f position;
    World* world;
};

#endif
