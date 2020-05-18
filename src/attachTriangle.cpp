#include <iostream>
#include "../include/attachTriangle.h"
#include "../include/entity.h"
#include "../include/utility.h"

AttachTriangle::AttachTriangle(Entity *entity, sf::Color color, float size, sf::Vector2f position, bool visibility, float rotation)
: Attachable(entity)
, color(color)
, shape(sf::CircleShape(size, 3))
, visible(visibility) {
    centerOrigin(shape);
    shape.setRotation(rotation);
    shape.setPosition(position);
    shape.setFillColor(color);
}

void AttachTriangle::draw(sf::RenderWindow &window) {
    if (!visible) {
        return;
    }
    sf::CircleShape tri = shape;
    tri.setPosition(tri.getPosition() + entity->getPosition());
    window.draw(tri);
}

bool AttachTriangle::getVisibility() {
    return visible;
}

void AttachTriangle::setVisibility(bool vis) {
    visible = vis;
}