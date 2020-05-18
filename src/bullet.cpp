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
  damage = 10;
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
  // hitbox->draw(window);
}

void SimpleBullet::update(sf::Time dt) {
  if (isTimeFlowing()) {
    sf::Vector2f acc = world->calcGravAccel(position);
    velocity += acc * dt.asSeconds();
    setPosition(position + velocity * dt.asSeconds());

    bullet.setPosition(position);
    hitbox->update();
    last_spawn += dt;
    if (last_spawn >= spawn_delay)
      spawn();
  }
}

sf::Time const SplitBullet::split_delay = sf::seconds(2.);

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

    life_span  += dt;
    last_spawn += dt;
    if (last_spawn >= spawn_delay)
      spawn();

    if (life_span >= split_delay)
      split();
  }
}

void SplitBullet::split() {
  sf::Vector2f left(velocity.y, velocity.x);
  sf::Vector2f right(-velocity.y, -velocity.x);
  left += velocity;
  right += velocity;
  world->spawnBullet(position, left, SIMPLE_F);
  world->spawnBullet(position, right, SIMPLE_F);
  world->removeEntity(this);
}

HeavyBullet::HeavyBullet(sf::Vector2f position, sf::Vector2f velocity)
: AbsBullet(position, velocity, 6.) {
  damage = 25;
}


void HeavyBullet::update(sf::Time dt) {
  if (isTimeFlowing()) {
    sf::Vector2f acc = world->calcGravAccel(position);
    acc += acc;
    velocity += acc * dt.asSeconds();
    setPosition(position + velocity * dt.asSeconds());

    bullet.setPosition(position);
    hitbox->update();
    last_spawn += dt;
    if (last_spawn >= spawn_delay)
      spawn();
  }
}