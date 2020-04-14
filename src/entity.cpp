#include "../include/entity.h"
#include "../include/utility.h"
#include "../include/boundingHitbox.h"

Entity::Entity(sf::Vector2f position, Entity::CollisionCategory category)
: collision_category(category)
, position(position)
, world(nullptr)
, hitbox(new BoundingHitbox{this}) {}

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

Entity::CollisionCategory Entity::getCategory() const {
    return collision_category;
}

void Entity::setCategory(Entity::CollisionCategory category) {
    collision_category = category;
}

bool Entity::doesCollide(Entity &entity) {
    return hitbox->doesIntersect(*entity.hitbox);
}

sf::Transform Entity::getTransform() const {
    return sf::Transform::Identity;
}

void Entity::move(sf::Vector2f vector) {
    position += vector;
}