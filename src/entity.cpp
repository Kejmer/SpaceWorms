#include "../include/entity.h"
#include "../include/utility.h"

Entity::Entity(sf::Vector2f position)
: position(position)
, world(nullptr) {}

void Entity::setPosition(sf::Vector2f position) {
    this->position = position;
}

sf::Vector2f Entity::getPosition() {
    return position;
}

void Entity::setWorld(World *world) {
    this->world = world;
}

World* Entity::getWorld() {
    return world;
}

//Odległość punktu od entity
float Entity::distanceTo(sf::Vector2f where) {
    return calcDistance(position, where);
}