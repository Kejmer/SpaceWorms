#include <cmath>
#include "../include/hole.h"
#include "../include/world.h"
#include "../include/utility.h"

GHole::GHole(sf::Vector2f position, float mass, float radius)
: Entity(position)
, mass(mass) {
  hole.setPosition(position);
  hole.setRadius(radius);

  centerOrigin(hole);
}

sf::Vector2f GHole::acceleration(sf::Vector2f where) {
  float dist = distanceTo(where);
  if (std::abs(dist) < eps) {
    return {0,0};
  }
  float coefficient = mass / (dist * dist);
  sf::Vector2f dirVect = (where - position) / dist;
  return dirVect * (coefficient * -1.f);
}

void GHole::input(sf::Event event) {}

//TODO Anita - jakaś animacja wirowania? nie Sprint-1
void GHole::update(sf::Time dt) {}

void GHole::draw(sf::RenderWindow& window) {
  window.draw(hole);
}

void GHole::setWorld(World *world) {
  if (this->world != world) {
    if (this->world != nullptr) {
      //usuń obiekt z poprzedniego world
    }
    this->world = world;
  }
}

BlackHole::BlackHole(sf::Vector2f position, float mass, float radius)
: GHole(position, mass, radius) {
  //kolor chwilowo aby było widoczne
  //TODO Anita texturki
  hole.setFillColor(sf::Color::White);
}

short BlackHole::direction() {
  return 1;
}