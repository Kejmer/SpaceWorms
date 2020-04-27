#ifndef ASTEROID_H
#define ASTEROID_H

#include "entity.h"

class Asteroid : public GHole {
public:
  Asteroid(sf::Vector2f position, float radius, float mass);
  sf::Vector2f acceleration(sf::Vector2f where);
  void draw(sf::RenderWindow& window);
  bool gravity;

protected:
  typedef GHole super;
  short direction();
};



#endif /* ASTEROID_H */