#include "../include/spaceship.h"
#include "../include/utility.h"
#include "../include/world.h"
#include "../include/bullet.h"
#include "../include/complexHitbox.h"

const float Spaceship::rotation_speed = 90;
const float Spaceship::shots_per_second = 3;
const float Spaceship::bullet_speed = 100;
const float Spaceship::ship_speed = 90;

int Spaceship::counter = 1;

Spaceship::Spaceship(sf::Vector2f position, sf::Color color)
: Entity(position, Entity::Spaceship)
, ship(30, 3)
, rotation(0)
, last_shot(sf::Time::Zero) {
    centerOrigin(ship);
    ship.setPosition(position);
    ship.setFillColor(color);
    id = counter++;

    createHitbox();
}

void Spaceship::input(sf::Event event) {}

void Spaceship::update(sf::Time dt) {
    if (id == world->getMoveRequest())
        world->clearRequest();

    last_shot += dt;

    if (id == world->getController()) {
        realtimeInput();

        sf::Vector2f direction = getDirection();
        move(direction * move_dir * ship_speed * dt.asSeconds());
        ship.rotate(dt.asSeconds() * rotation * rotation_speed);
        rotation = 0;
        move_dir = 0;

        hitbox->update();
    }
}

void Spaceship::draw(sf::RenderWindow& window) {
    window.draw(ship);
    // hitbox->draw(window);
}

void Spaceship::shoot() {
    sf::Vector2f direction = getDirection();
    world->addEntity(new SimpleBullet{position + direction * 35.f, direction * bullet_speed});
    last_shot = sf::Time::Zero;

    world->nextTurn();
}

void Spaceship::move(sf::Vector2f vector) {
    Entity::move(vector);
    ship.move(vector);
}

void Spaceship::realtimeInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        world->moveRequest(id);
        move_dir += 1;
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        world->moveRequest(id);
        move_dir -= 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
        last_shot.asSeconds() >= 1. / shots_per_second)
        shoot();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        rotation += 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        rotation -= 1;
}

sf::Vector2f Spaceship::getDirection() {
    float rotation = toRadian(ship.getRotation());
    return {sinf(rotation), -cosf(rotation)};
}

void Spaceship::createHitbox() {
    hitbox = std::unique_ptr<ComplexHitbox>(new ComplexHitbox{this, &ship});
    sf::FloatRect bounds = ship.getLocalBounds();
    sf::RectangleShape rect{{30, 30}};
    rect.setPosition(0, -ship.getOrigin().y);
    rect.rotate(45);
    hitbox->addRectangle(rect);

    rect.setSize({20, 20});
    centerOrigin(rect);
    rect.setPosition({-ship.getOrigin().x / 2, (bounds.height - ship.getOrigin().y) / 2});
    rect.rotate(-90);
    hitbox->addRectangle(rect);

    rect.move({-2 * rect.getPosition().x, 0});
    hitbox->addRectangle(rect);

    rect.move({-rect.getPosition().x, 0});
    rect.rotate(45);
    hitbox->addRectangle(rect);
}

int Spaceship::getID() {
    return id;
}