#include <cmath>
#include "../include/bullet.h"
#include "../include/world.h"
#include "../include/boundingHitbox.h"
#include "../include/trace.h"

sf::Time const SimpleBullet::spawn_delay = sf::seconds(1./5.);

SimpleBullet::SimpleBullet(sf::Vector2f position, sf::Vector2f velocity)
: Entity(position, Entity::Bullet)
, bullet(2.)
, velocity(velocity)
, last_spawn(sf::Time::Zero) {
  bullet.setPosition(position);
  bullet.setFillColor(sf::Color::White);

  sf::FloatRect bounds = bullet.getLocalBounds();
  bullet.setOrigin(std::floor(bounds.left + bounds.width / 2.),
                   std::floor(bounds.top + bounds.height / 2.));

  hitbox = std::unique_ptr<BoundingHitbox>(new BoundingHitbox{this, &bullet});
}

void SimpleBullet::input(sf::Event event) {}

void SimpleBullet::update(sf::Time dt) {
  if (isTimeFlowing()) {
    sf::Vector2f acc = world->calcGravAccel(position);
    velocity += acc * dt.asSeconds();
    setPosition(position + velocity * dt.asSeconds());

    bullet.setPosition(position);
    hitbox->update();
    last_spawn += dt;
    if (last_spawn >= spawn_delay) {
      spawn();
    }
  }
}

void SimpleBullet::draw(sf::RenderWindow& window) {
  window.draw(bullet);
  // hitbox->draw(window);
}

void SimpleBullet::spawn() {
  last_spawn = sf::Time::Zero;
  world->addEntity(new Trace(position));
}