#include <cmath>
#include "../include/hole.h"
#include "../include/world.h"

GHole::GHole(sf::Vector2f position, float mass, float radius)
: Entity(position)
, mass(mass) {
  hole.setPosition(position);
  hole.setRadius(radius);

  sf::FloatRect bounds = hole.getLocalBounds();
  hole.setOrigin(std::floor(bounds.left + bounds.width / 2.),
                 std::floor(bounds.top + bounds.height / 2.));

}

sf::Vector2f GHole::acceleration(sf::Vector2f where) {
  float dist = distanceTo(where);
  float coefficient = mass / (dist * dist);
  sf::Vector2f dirVect = where - position / dist;
  return dirVect * coefficient;
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
    world->addHoleEntity(this);
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