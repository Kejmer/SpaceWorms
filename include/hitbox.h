#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

#include "attachable.h"

// Forward declaration
class Entity;

class Hitbox : public Attachable {
public:
    Hitbox(Entity *entity);
    virtual ~Hitbox() = default;

    virtual void update() = 0;

    virtual void addRectangle(sf::RectangleShape rectangle);
    bool doesIntersect(Hitbox &hitbox);
    std::vector<sf::RectangleShape> *getRectangles();
    Entity *getEntity();

    // For testing
    void draw(sf::RenderWindow &window);
private:
    bool doRectanglesIntersect(sf::RectangleShape &rect1, sf::RectangleShape &rect2);
protected:
    std::vector<sf::RectangleShape> rectangles;
};

#endif