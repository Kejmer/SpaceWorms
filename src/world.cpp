#include "../include/world.h"

const sf::Time World::frame_time = sf::seconds(1./60.);

World::World(sf::RenderWindow& window)
: window(window)
, entities()
, pending_changes()
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

    applyPendingChanges();
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

void World::addEntity(Entity* entity) {
    entity->setWorld(this);
    pending_changes.push_back({Add, entity});
}

void World::removeEntity(Entity* entity) {
    pending_changes.push_back({Remove, entity});
}

bool World::isTimeFlowing() {
    return is_time_flowing;
}

void World::applyPendingChanges() {
    for (auto& change : pending_changes)
        switch (change.action) {
            case Add:
                entities.push_back(std::unique_ptr<Entity>(change.entity));
                break;

            case Remove:
                for (auto it = entities.begin(); it != entities.end(); it++)
                    if ((*it).get() == change.entity) {
                        (*it).get()->setWorld(nullptr);
                        entities.erase(it);
                    }
        }

    pending_changes.clear();
}