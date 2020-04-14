#include "../include/spaceship.h"
#include "../include/utility.h"
#include "../include/world.h"
#include "../include/bullet.h"
#include "../include/boundingHitbox.h"

const float Spaceship::rotation_speed = 90;
const float Spaceship::shots_per_second = 3;
const float Spaceship::bullet_speed = 100;
const float Spaceship::ship_speed = 70;

Spaceship::Spaceship(sf::Vector2f position) 
: Entity(position, Entity::Spaceship)
, ship(30, 3)
, rotation(0)
, last_shot(sf::Time::Zero) {
    centerOrigin(ship);
    ship.setPosition(position);
    ship.setFillColor(sf::Color::Red);

    hitbox = std::unique_ptr<BoundingHitbox>(new BoundingHitbox{this, &ship});
}

void Spaceship::input(sf::Event event) {}

void Spaceship::update(sf::Time dt) {
    last_shot += dt;

    realtimeInput();

    sf::Vector2f direction = getDirection();
    move(direction * move_dir * bullet_speed * dt.asSeconds());
    ship.rotate(dt.asSeconds() * rotation * rotation_speed);
    rotation = 0;
    move_dir = 0;

    hitbox->update();
}

void Spaceship::draw(sf::RenderWindow& window) {
    window.draw(ship);
    hitbox->draw(window);

    sf::CircleShape eee{3};
    centerOrigin(eee);
    eee.setPosition(ship.getPosition());
    eee.setFillColor(sf::Color::Blue);
    // sf::FloatRect e = ship.getLocalBounds();
    // sf::RectangleShape eee;
    // eee.setPosition({e.left, e.top});
    // eee.setSize({e.width, e.height});
    // eee.setOrigin(ship.getOrigin());
    // eee.move(ship.getPosition());
    // eee.setFillColor(sf::Color::Transparent);
    // eee.setOutlineThickness(1);
    // eee.setOutlineColor(sf::Color::Yellow);
    window.draw(eee);
}

void Spaceship::shoot() {}

void Spaceship::move(sf::Vector2f vector) {
    Entity::move(vector);
    ship.move(vector);
}

void Spaceship::realtimeInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) 
        move_dir += 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        move_dir -= 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        rotation += 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        rotation -= 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && 
        last_shot.asSeconds() >= 1. / shots_per_second) {

        sf::Vector2f direction = getDirection();
        world->addEntity(new SimpleBullet{position + direction * 35.f, direction * bullet_speed});
        last_shot = sf::Time::Zero;
    } 
}

sf::Vector2f Spaceship::getDirection() {
    float rotation = toRadian(ship.getRotation());
    return {sinf(rotation), -cosf(rotation)};
}
