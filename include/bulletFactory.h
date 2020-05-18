#ifndef BULLET_FACTORY_H
#define BULLET_FACTORY_H

#include "bullet.h"

class AbsBulletFactory {
public:
  AbsBulletFactory() = default;
  virtual ~AbsBulletFactory() = default;
  virtual AbsBullet *spawn(sf::Vector2f position, sf::Vector2f velocity) = 0;
};

class SimpleBulletFactory : public AbsBulletFactory {
public:
  SimpleBulletFactory() = default;
  ~SimpleBulletFactory() = default;
  AbsBullet *spawn(sf::Vector2f position, sf::Vector2f velocity);
};

class SplitBulletFactory : public AbsBulletFactory {
public:
  SplitBulletFactory() = default;
  ~SplitBulletFactory() = default;
  AbsBullet *spawn(sf::Vector2f position, sf::Vector2f velocity);
};

class HeavyBulletFactory : public AbsBulletFactory {
public:
  HeavyBulletFactory() = default;
  ~HeavyBulletFactory() = default;
  AbsBullet *spawn(sf::Vector2f position, sf::Vector2f velocity);
};

#endif /* BULLLET_FACTORY_H */