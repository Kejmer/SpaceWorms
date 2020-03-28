#include "../include/bullet.h"

#include <cmath>

SimpleBullet::SimpleBullet(sf::Vector2f position, sf::Vector2f velocity)
: Entity(position)
, bullet(2.)
, velocity(velocity) {
  bullet.setPosition(position);
  bullet.setFillColor(sf::Color::White);

  sf::FloatRect bounds = bullet.getLocalBounds();
  bullet.setOrigin(std::floor(bounds.left + bounds.width / 2.),
                   std::floor(bounds.top + bounds.height / 2.));
}

void SimpleBullet::input(sf::Event event) {}

void SimpleBullet::update(sf::Time dt) {
  setPosition(position + velocity * dt.asSeconds());
  bullet.setPosition(position);
}

void SimpleBullet::draw(sf::RenderWindow& window) {
  window.draw(bullet);
}