#include "../include/healthPowerUp.h"

HealthPowerUp::HealthPowerUp(sf::Vector2f pos)
: PowerUp(sf::Color::Green, pos) {}

void HealthPowerUp::applyEffect(class Spaceship *ship) {
    ship->updateStatistics(Spaceship::Healthpoints, ship->getStatistics(Spaceship::Healthpoints) + strength);
}