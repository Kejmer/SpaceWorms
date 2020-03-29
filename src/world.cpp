#include "../include/world.h"

const sf::Time World::frame_time = sf::seconds(1./60.);

World::World(sf::RenderWindow& window)
: window(window)
, entities()
, is_time_flowing(false) {}

void World::input() {
    sf::Event event;
    while (window.pollEvent(event)) {
        for (auto& entity : entities)
            entity->input(event);

        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void World::update(sf::Time dt) {
    for (auto& entity : entities)
        entity->update(dt);

    entities.applyPendingChanges();
}

void World::draw() {
    //TODO Anita tło
    window.clear(sf::Color::Black);
    for (auto& entity : entities)
        entity->draw(window);

    window.display();
}

void World::run() {
    sf::Clock clock;
    sf::Time last_update = sf::Time::Zero;

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        last_update += elapsed;
        while (last_update > frame_time) {
            last_update -= frame_time;

            is_time_flowing = false;
            input();
            update(frame_time);
        }
        draw();
    }
}

std::shared_ptr<Entity> World::addEntity(Entity* entity) {
    entity->setWorld(this);
    return entities.add(entity);
}

void World::addEntity(std::shared_ptr<Entity> entity) {
    entity->setWorld(this);
    entities.add(entity);
}

void World::removeEntity(Entity* entity) {
    entities.remove(entity);
}

bool World::isTimeFlowing() {
    return is_time_flowing;
}