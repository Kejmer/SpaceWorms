#include "../include/world.h"
#include "../include/collisions.h"
#include "../include/bar.h"
#include "../include/healthPowerUp.h"
#include "../include/timePowerUp.h"
#include "../include/ammoPowerUp.h"
#include "../include/powerUp.h"
#include "../include/screenHolder.h"
#include "../include/pause.h"
#include "../include/endingScreen.h"

#include <SFML/Config.hpp>

const sf::Time World::turn_time = sf::seconds(2.);

World::World(sf::RenderWindow& window, ScreenHolder& screen_holder)
: Screen(window, screen_holder)
, requesterId(0)
, is_time_flowing(false)
, teams_remaining(0)
, current_team(0)
, current_ship(0) {
    time_left = turn_time;
    game_speed_bar = std::unique_ptr<Bar>(new Bar{nullptr, sf::Color::White, sf::Color::Yellow, {200, 20}, {100, 10}, max_time_mult, time_multiplier});
    game_speed_text = std::unique_ptr<TextBox>(new TextBox{nullptr, "Game speed", {40, 10}, 14});
    game_speed_text->setColor(sf::Color::Black);
    background_texture.loadFromFile("assets/background.png");
    Spaceship::resetCounter();
    Team::resetCounter();
}

bool World::input(sf::Event event) {
    for (auto& entity : entities)
        entity->input(event);

    if (is_time_flowing) {

    } else {
        userTeamControl(event);
    }

    return false;
}

bool World::update(sf::Time dt) {
    timeMultiplierChanges();

    dt *= time_multiplier;
    for (auto& entity : entities)
        entity->update(dt);

    checkCollisions();

    if (is_time_flowing)
        time_left -= dt;

    if (time_left <= sf::Time::Zero) {
        if (teams_remaining <= 1) {
            screen_holder.clear();
            if (teams.size() == 0)
                screen_holder.push_back(new EndingScreen(window, screen_holder, nullptr));
            else
                screen_holder.push_back(new EndingScreen(window, screen_holder, teams[0].get()));

            sf::sleep(sf::seconds(1));
        }

        nextTeam();
        time_left = turn_time;
        is_time_flowing = false;
    }

    entities.applyPendingChanges();
    holeEntities.applyPendingChanges();
    pauseMenu();

    return false;
}

bool World::draw() {
    // window.clear(sf::Color::Black);
    // window.setTexture(texture);
    sf::Sprite sprite(background_texture);
    window.draw(sprite);

    for (auto& entity : entities)
        entity->draw(window);

    game_speed_bar->draw(window);
    game_speed_text->draw(window);
    return false;
}

void World::run() {
    nextTeam();
}

std::shared_ptr<Entity> World::addEntity(Entity* entity) {
    entity->setWorld(this);
    return Screen::addEntity(entity);
}

void World::addEntity(std::shared_ptr<Entity> entity) {
    entity->setWorld(this);
    Screen::addEntity(entity);
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
        if (h->gravity == true) {
            res += h->acceleration(pos);
        }
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

void World::moveRequest(int spaceship_id) {
    if (!is_time_flowing) {
        is_time_flowing = true;
        requesterId = spaceship_id;
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
    teams_remaining++;
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

void World::newPowerUp(sf::Vector2f position, PowerUp::PowerUpType type) {
    switch(type) {
        case PowerUp::Health:
            this->addEntity(new HealthPowerUp(position));
            break;
        case PowerUp::Ammo:
            this->addEntity(new AmmoPowerUp(position));
            break;
        case PowerUp::Time:
            this->addEntity(new TimePowerUp(position));
            break;
    }
}

void World::userTeamControl(sf::Event event) {
    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::N)
            controlNext();
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

void World::timeMultiplierChanges() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen) && time_multiplier > 0) {
        time_multiplier -= 0.1;
        game_speed_bar->setValue(time_multiplier);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal) && time_multiplier < max_time_mult) {
        time_multiplier += 0.1;
        game_speed_bar->setValue(time_multiplier);
    }
}

void World::extendTurn(sf::Time t) {
    time_left += t;
}

void World::shipDestroyed(int team_id, int ship_id) {
    int i = 0;
    bool remove = false;
    for (auto t : teams) {
        if (t->getID() == team_id) {
            t->removeShip(ship_id);
            if (t->size() == 0) {
                remove = true;
                teams_remaining--;
            }
            break;
        }
        i++;
    }
    if (remove)
        teams.erase(teams.begin() + i);
}

void World::pauseMenu() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::P))
        screen_holder.push_back(new Pause(window, screen_holder));
}
