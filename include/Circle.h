#ifndef CIRCLE_H
#define CIRCLE_H

#include "Entity.h"

// Temporary class just for testing

class Circle : public Entity {
public:
    Circle(sf::Vector2f position, float radius, sf::Color color);
    void input(sf::Event event);
    void update(sf::Time dt);
    void draw(sf::RenderWindow& window);
private:
    sf::CircleShape circle;
};

#endif