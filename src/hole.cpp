#include <cmath>
#include "../include/hole.h"
#include "../include/world.h"
#include "../include/utility.h"
#include "../include/boundingHitbox.h"

GHole::GHole(sf::Vector2f position, float mass, float radius, int gravity)
: Entity(position, Entity::Hole)
, gravity(gravity)
, mass(mass) {
  hole.setPosition(position);
  hole.setRadius(radius);

  centerOrigin(hole);

  hitbox = std::unique_ptr<BoundingHitbox>(new BoundingHitbox{this, &hole});
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
  // hitbox->draw(window);
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
: GHole(position, mass, radius, 1) {
  //kolor chwilowo aby było widoczne
  texture.loadFromFile("assets/blackhole2.png"); // Może rzucić failem, jeśli nie załaduje obrazka, wtedy ładuje biały trójkąt. 
  hole.setTexture(&texture, true);
  hole.setFillColor(sf::Color::White);
}

short BlackHole::direction() {
  return 1;
}

WhiteHole::WhiteHole(sf::Vector2f position, float mass, float radius)
: GHole(position, mass, radius, 1) {
  //kolor chwilowo aby było widoczne
  texture.loadFromFile("assets/whitehole.png"); // Może rzucić failem, jeśli nie załaduje obrazka, wtedy ładuje biały trójkąt. 
  hole.setTexture(&texture, true);
  hole.setFillColor(sf::Color::White);
}

short WhiteHole::direction() {
  return -1;
}