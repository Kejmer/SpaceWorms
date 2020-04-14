#include "../include/complexHitbox.h"
#include "../include/utility.h"

ComplexHitbox::ComplexHitbox(Entity *entity, sf::Transformable *shape)
: Hitbox(entity)
, shape(shape)
, initialRectangles() {}

void ComplexHitbox::addRectangle(sf::RectangleShape rect) {
    initialRectangles.push_back(rect);
    rectangles.push_back(rect);
}

void ComplexHitbox::update() {
    rectangles.clear();

    for (auto rect : initialRectangles) {
        rect.move(shape->getPosition());
        rect.rotate(shape->getRotation());
        sf::Vector2f pos = rect.getPosition();
        pos -= shape->getPosition();
        float angle = toRadian(shape->getRotation());
        sf::Vector2f rotatedPos = {cosf(angle) * pos.x - sinf(angle) * pos.y,
                                   sinf(angle) * pos.x + cosf(angle) * pos.y};
        rotatedPos += shape->getPosition();
        rect.setPosition(rotatedPos);
        rectangles.push_back(rect);
    }
}