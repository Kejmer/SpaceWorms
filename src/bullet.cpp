#include <cmath>
#include "../include/bullet.h"
#include "../include/world.h"
#include "../include/boundingHitbox.h"
#include "../include/trace.h"

sf::Time const AbsBullet::spawn_delay = sf::seconds(1./5.);

AbsBullet::AbsBullet(sf::Vector2f position, sf::Vector2f velocity, float bullet_size)
: Entity(position, Entity::Bullet)
, bullet(bullet_size)
, velocity(velocity)
, last_spawn(sf::Time::Zero) {
  bullet.setFillColor(sf::Color::White);
  bullet.setPosition(position);

  sf::FloatRect bounds = bullet.getLocalBounds();
  bullet.setOrigin(std::floor(bounds.left + bounds.width / 2.),
                   std::floor(bounds.top + bounds.height / 2.));

  hitbox = std::unique_ptr<BoundingHitbox>(new BoundingHitbox{this, &bullet});
}

void AbsBullet::spawn() {
  last_spawn = sf::Time::Zero;
  world->addEntity(new Trace(position));
}

void AbsBullet::input(sf::Event event) {}

SimpleBullet::SimpleBullet(sf::Vector2f position, sf::Vector2f velocity)
: AbsBullet(position, velocity, 2.) {
}

void AbsBullet::draw(sf::RenderWindow& window) {
  window.draw(bullet);
  hitbox->draw(window);
}

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

SplitBullet::SplitBullet(sf::Vector2f position, sf::Vector2f velocity)
: AbsBullet(position, velocity, 4.) {
}


void SplitBullet::update(sf::Time dt) {
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
