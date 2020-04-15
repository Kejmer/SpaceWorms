#include "../include/boundingHitbox.h"

#include "../include/utility.h"

BoundingHitbox::BoundingHitbox(Entity *entity)
: Hitbox(entity)
, shape(nullptr) {}

BoundingHitbox::BoundingHitbox(Entity *entity, sf::Shape *shape) 
: Hitbox(entity)
, shape(shape) {
    update();
}

void BoundingHitbox::update() {
    rectangles.clear();
    sf::FloatRect bounds = shape->getLocalBounds();
    sf::RectangleShape newRect{sf::Vector2f{bounds.width, bounds.height}};
    newRect.setOrigin(shape->getOrigin() - sf::Vector2f{bounds.left, bounds.top});
    newRect.setPosition(shape->getPosition());
    newRect.rotate(shape->getRotation());
    rectangles.push_back(newRect);
}