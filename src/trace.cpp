#include <cmath>
#include "../include/trace.h"
#include "../include/world.h"

sf::Time const Trace::Decay_rate = sf::seconds(1./60.);

Trace::Trace(sf::Vector2f position)
: Entity(position, Entity::None)
, last_update(sf::Time::Zero)
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
    // last_update += dt;
    alpha--;
    // alpha -= last_update / decayRate;
    // last_update %= decayRate;
    trace.setFillColor(sf::Color(255,255,255,alpha));
    if (alpha <= 0)
      world->removeEntity(this);
  }
}

void Trace::draw(sf::RenderWindow& window) {
  window.draw(trace);
}