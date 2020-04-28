#include <algorithm>
#include "../include/healthPowerUp.h"

HealthPowerUp::HealthPowerUp(sf::Vector2f pos)
: PowerUp(sf::Color::Green, pos) {
	texture.loadFromFile("assets/health_bonus.png"); // Może rzucić failem, jeśli nie załaduje obrazka, wtedy ładuje biały trójkąt. 
  	// shape.setTexture(&texture, false);
}

void HealthPowerUp::applyEffect(class Spaceship *ship) {
	float new_val = std::min(ship->getStatistics(Spaceship::Healthpoints) + strength, ship->getStatistics(Spaceship::MaxHealth));
    ship->updateStatistics(Spaceship::Healthpoints, new_val);
}