#include "../include/entity.h"
#include "../include/utility.h"
#include "../include/boundingHitbox.h"
#include "../include/world.h"

Entity::Entity(sf::Vector2f position, Entity::CollisionCategory category)
: collision_category(category)
, damage(0)
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

void Entity::setScreen(Screen *screen) {
    this->screen = screen;
}

Screen* Entity::getScreen() {
    return screen;
}

void Entity::despawn() {
    world->removeEntity(this);
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

void Entity::addAttachable(Attachable *att) {
    attachables_to_draw.push_back(std::shared_ptr<Attachable>(att));
}

void Entity::addAttachable(std::shared_ptr<Attachable> att) {
    attachables_to_draw.push_back(att);
}

void Entity::removeAttachable(Attachable *att) {
    for (auto it = attachables_to_draw.begin(); it != attachables_to_draw.end(); it++)
        if (it->get() == att) {
            attachables_to_draw.erase(it);
            break;
        }
}

int Entity::getDamage() {
    return damage;
}