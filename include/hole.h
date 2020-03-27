#ifndef HOLE_H
#define HOLE_H

#include "entity.h"

class GHole : public Entity {
public:
  GHole(sf::Vector2f position, float mass, float radius);
  sf::Vector2f acceleration(sf::Vector2f where);

  void input(sf::Event event);
  void update(sf::Time dt);
  void draw(sf::RenderWindow& window);
  void setWorld(World *world);
protected:
  typedef Entity super;
  // virtual short direction(); //może static? TODO Michał ale nie ten sprint | coś się nie kompiluje więc do naprawienia potem
  float mass;
  sf::CircleShape hole;
};

class BlackHole : public GHole {
public:
  BlackHole(sf::Vector2f position, float mass, float radius);
protected:
  typedef GHole super;
  short direction();
};

#endif /* HOLE_H */