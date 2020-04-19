#include <cmath>
#include "../include/trace.h"
#include "../include/world.h"

Trace::Trace(sf::Vector2f position)
: Entity(position, Entity::None)
, trace(1.)
, alpha(255)
{
   trace.setPosition(position);

  sf::FloatRect bounds = trace.getLocalBounds();
  trace.setOrigin(std::floor(bounds.left + bounds.width / 2.),
                  std::floor(bounds.top + bounds.height / 2.));
}

void Trace::input(sf::Event event) {}

void Trace::update(sf::Time dt) {
  if (isTimeFlowing()) {
    alpha--;
    trace.setFillColor(sf::Color(255,255,255,alpha));
    if (alpha <= 0)
      world->removeEntity(this);
  }
}

void Trace::draw(sf::RenderWindow& window) {
  window.draw(trace);
}