#include "../include/world.h"
#include "../include/collisions.h"

const sf::Time World::frame_time = sf::seconds(1./60.);

World::World(sf::RenderWindow& window)
: window(window)
, entities()
, is_time_flowing(true) {}

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
    // if poniżej to fragment prezentujący funkcjonalność,
    // zostanie usunięty po dodaniu slidera czasu (życzenia inwestora)
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::T)) {
        is_time_flowing = !is_time_flowing;
    }

    checkCollisions();

    entities.applyPendingChanges();
    holeEntities.applyPendingChanges();
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

void World::addHoleEntity(GHole* hole) {
    hole->setWorld(this);
    auto ptr = holeEntities.add(hole);
    entities.add(ptr);
}

void World::removeHoleEntity(GHole *hole) {
    holeEntities.remove(hole);
    entities.remove(hole);
}

void World::removeEntity(Entity* entity) {
    entities.remove(entity);
}

sf::Vector2f World::calcGravAccel(sf::Vector2f pos) {
    sf::Vector2f res(0, 0);
    for (std::shared_ptr<GHole> h : holeEntities) {
        res += h->acceleration(pos);
    }
    return res * gravity_multiplier;
}

bool World::isTimeFlowing() {
    return is_time_flowing;
}

bool Entity::isTimeFlowing() {
    return world->isTimeFlowing();
}

void World::checkCollisions() {
    for (unsigned int i = 0; i < entities.size(); i++)
        for (unsigned int j = i + 1; j < entities.size(); j++)
            if (entities[i]->doesCollide(*entities[j])) 
                collide(entities[i].get(), entities[j].get());
}