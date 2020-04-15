#ifndef BOUNDINGHITBOX_H
#define BOUNDINGHITBOX_H

#include "hitbox.h"

class BoundingHitbox : public Hitbox {
public:
    BoundingHitbox(Entity *entity);
    BoundingHitbox(Entity *entity, sf::Shape *shape);

    void update();
private:
    sf::Shape *shape;
};

#endif