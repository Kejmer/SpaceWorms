#ifndef ASTEROID_H
#define ASTEROID_H

#include "entity.h"

class Asteroid : public GHole {
public:
  Asteroid(sf::Vector2f position, float mass, float radius);
  sf::Vector2f acceleration(sf::Vector2f where);
  void draw(sf::RenderWindow& window);
protected:
  typedef GHole super;
  short direction();
};



#endif /* ASTEROID_H */