#include "../include/screen.h"

Screen::Screen(sf::RenderWindow& window, ScreenHolder& screen_holder)
: window(window)
, screen_holder(screen_holder)
, entities() {}

bool Screen::input(sf::Event event) {
    for (auto& entity : entities)
        entity->input(event);
    
    return false;
}

bool Screen::update(sf::Time dt) {
    for (auto& entity : entities)
        entity->update(dt);

    return false;
}

bool Screen::draw() {
    for (auto& entity : entities)
        entity->draw(window);

    return false;
}

std::shared_ptr<Entity> Screen::addEntity(Entity* entity) {
    entity->setScreen(this);
    return entities.add(entity);
}

void Screen::addEntity(std::shared_ptr<Entity> entity) {
    entity->setScreen(this);
    entities.add(entity);
}

void Screen::removeEntity(Entity* entity) {
    entities.remove(entity);
}