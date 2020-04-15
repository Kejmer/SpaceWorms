#ifndef COMPLEXHITBOX_H
#define COMPLEXHITBOX_H

#include "hitbox.h"

class ComplexHitbox : public Hitbox {
public:
    ComplexHitbox(Entity *entity, sf::Transformable *shape);
    void addRectangle(sf::RectangleShape rect);

    void update();
private:
    sf::Transformable *shape;
    std::vector<sf::RectangleShape> initialRectangles;
};

#endif