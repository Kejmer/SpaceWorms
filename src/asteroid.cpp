#include <cmath>
#include "../include/hole.h"
#include "../include/world.h"
#include "../include/utility.h"
#include "../include/boundingHitbox.h"
#include "../include/asteroid.h"

Asteroid::Asteroid(sf::Vector2f position, float mass, float radius)
: GHole(position, mass, radius, 0) {
  texture.loadFromFile("assets/asteroid.png"); // Może rzucić failem, jeśli nie załaduje obrazka, wtedy ładuje biały trójkąt. 
  hole.setTexture(&texture, true);
}


sf::Vector2f Asteroid::acceleration(sf::Vector2f where) {
  return where;
}

void Asteroid::draw(sf::RenderWindow& window) {
  window.draw(hole);
  // hitbox->draw(window);
}


short Asteroid::direction() {
  return 0;
}
