#include "../include/world.h"
#include "../include/collisions.h"

const sf::Time World::frame_time = sf::seconds(1./60.);
const sf::Time World::turn_time = sf::seconds(2.);

World::World(sf::RenderWindow& window)
: window(window)
, entities()
, requesterId(0)
, is_time_flowing(false)
, current_team(0)
, current_ship(0) {
    time_left = turn_time;
}

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

    if (is_time_flowing)
        time_left -= dt;

    if (time_left <= sf::Time::Zero) {
        nextTeam();
        time_left = turn_time;
        is_time_flowing = false;
    }

    checkCollisions();

    entities.applyPendingChanges();
    holeEntities.applyPendingChanges();
}

void World::draw() {
    sf::Texture texture;
    texture.loadFromFile("assets/background.png");

    // window.clear(sf::Color::Black);
    // window.setTexture(texture);
    sf::Sprite sprite(texture);
    window.clear(sf::Color::Black);
    window.draw(sprite);

    for (auto& entity : entities)
        entity->draw(window);

    window.display();
}

void World::run() {
    sf::Clock clock;
    sf::Time last_update = sf::Time::Zero;
    nextTeam();

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

void World::moveRequest(int spaceshipId) {
    if (!is_time_flowing) {
        is_time_flowing = true;
        requesterId = spaceshipId;
    }
}

int World::getMoveRequest() {
    return requesterId;
}

void World::clearRequest() {
    requesterId = 0;
    is_time_flowing = false;
}

int World::newTeam(sf::Color color) {
    auto ptr = std::make_shared<Team>(color);
    ptr->setWorld(this);
    teams.push_back(ptr);
    return ptr->getID();
}

void World::newShip(sf::Vector2f postion, int teamID) {
    for (auto t : teams) {
        if (t->getID() == teamID) {
            this->addEntity(t->addShip(postion));
            break;
        }
    }
}

void World::controlNext() {
    std::shared_ptr<Team> team = teams[current_team];
    current_ship = team->nextShip();
}

int World::nextTeam() {
    if (teams.size() == 0)
        return 0;
    current_team++;
    current_team %= teams.size();
    controlNext();
    return current_team;
}

int World::getController() {
    return current_ship;
}

void World::nextTurn() {
    current_ship = 0;
    is_time_flowing = true;
}