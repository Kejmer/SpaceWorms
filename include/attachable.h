#ifndef ATTACHABLE_H
#define ATTACHABLE_H

#include <SFML/Graphics.hpp>

// Forward declaration
class Entity;

class Attachable {
public:
    Attachable(Entity *entity);

    virtual void draw(sf::RenderWindow &window) = 0;
protected:
    Entity *entity;
};

#endif