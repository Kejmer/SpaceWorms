#include "../include/entity.h"

Entity::Entity(sf::Vector2f position)
: position(position) {}

void Entity::setPosition(sf::Vector2f position) {
    this->position = position;
}

sf::Vector2f Entity::getPosition() {
    return position;
}