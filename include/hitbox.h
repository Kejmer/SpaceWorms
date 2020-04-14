#ifndef HITBOX_H
#define HITBOX_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

// Forward declaration
class Entity;

class Hitbox {
public:
    Hitbox(Entity *entity);

    virtual void update() = 0;

    // void addRectangle(sf::RectangleShape *rectangle);
    bool doesIntersect(Hitbox &hitbox);
    std::vector<sf::RectangleShape> *getRectangles();
    Entity *getEntity();

    // For testing
    void draw(sf::RenderWindow &window);
private:
    bool doRectanglesIntersect(sf::RectangleShape &rect1, sf::RectangleShape &rect2);
protected:
    Entity *entity;
    std::vector<sf::RectangleShape> rectangles;
};

#endif