#include "../include/bulletFactory.h"

AbsBullet *SimpleBulletFactory::spawn(sf::Vector2f position, sf::Vector2f velocity) {
  return new SimpleBullet(position, velocity);
}

AbsBullet *SplitBulletFactory::spawn(sf::Vector2f position, sf::Vector2f velocity) {
  return new SplitBullet(position, velocity);
}