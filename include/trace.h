#ifndef TRACE_H
#define TRACE_H

#include "entity.h"

class Trace : public Entity {
public:
  Trace(sf::Vector2f position);
  void input(sf::Event event);
  void update(sf::Time dt);
  void draw(sf::RenderWindow& window);

private:
  static const sf::Time Decay_rate;
  sf::Time last_update;
  sf::CircleShape trace;
  sf::Color color;
  int alpha;
};

#endif /* TRACE_H */