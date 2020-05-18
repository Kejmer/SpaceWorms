#ifndef HOLE_H
#define HOLE_H

#include "entity.h"

class GHole : public Entity {
public:
  GHole(sf::Vector2f position, float mass, float radius, int gravity);
  virtual ~GHole() = default;
  sf::Vector2f acceleration(sf::Vector2f where);
  const int gravity;
  void input(sf::Event event);
  void update(sf::Time dt);
  void draw(sf::RenderWindow& window);
  void setWorld(World *world);
  virtual short direction() = 0; //może static? TODO Michał ale nie ten sprint

protected:
  typedef Entity super;
  float mass;
  sf::CircleShape hole;
  sf::Texture texture;

};

class BlackHole : public GHole {
public:
  BlackHole(sf::Vector2f position, float mass, float radius);
  // const int gravity;
protected:
  typedef GHole super;
  short direction();
};


class WhiteHole : public GHole {
public:
  WhiteHole(sf::Vector2f position, float mass, float radius);
  // const int gravity;
protected:
  typedef GHole super;
  short direction();
};


#endif /* HOLE_H */