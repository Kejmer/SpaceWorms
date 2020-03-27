#include "../include/spaceship.h"
#include "../include/utility.h"
#include "../include/world.h"
#include "../include/bullet.h"

const float Spaceship::rotation_speed = 90;
const float Spaceship::shots_per_second = 3;
const float Spaceship::bullet_speed = 50;

Spaceship::Spaceship(sf::Vector2f position) 
: Entity(position)
, ship(30, 3)
, rotation(0)
, last_shot(sf::Time::Zero) {
    centerOrigin(ship);
    ship.setPosition(position);
    ship.setFillColor(sf::Color::Red);
}

void Spaceship::input(sf::Event event) {}

void Spaceship::update(sf::Time dt) {
    last_shot += dt;

    realtimeInput();

    ship.rotate(dt.asSeconds() * rotation * rotation_speed);
    rotation = 0;
}

void Spaceship::draw(sf::RenderWindow& window) {
    window.draw(ship);
}

void Spaceship::shoot() {}

void Spaceship::realtimeInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        rotation += 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        rotation -= 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && 
        last_shot.asSeconds() >= 1. / shots_per_second) {

        float rotation = toRadian(ship.getRotation());
        sf::Vector2f direction{sinf(rotation), -cosf(rotation)};
        world->addEntity(new SimpleBullet{position + direction * 35.f, direction * bullet_speed});
        last_shot = sf::Time::Zero;
    } 
}