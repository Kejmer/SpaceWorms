#include "../include/bulletFactory.h"

AbsBullet *SimpleBulletFactory::spawn(sf::Vector2f position, sf::Vector2f velocity) {
  return new SimpleBullet(position, velocity);
}

AbsBullet *SplitBulletFactory::spawn(sf::Vector2f position, sf::Vector2f velocity) {
  return new SplitBullet(position, velocity);
}

AbsBullet *HeavyBulletFactory::spawn(sf::Vector2f position, sf::Vector2f velocity) {
  return new HeavyBullet(position, {velocity.x * 0.5f, velocity.y * 0.5f});
}
