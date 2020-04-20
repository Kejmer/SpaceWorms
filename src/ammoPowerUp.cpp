#include "../include/ammoPowerUp.h"

AmmoPowerUp::AmmoPowerUp(sf::Vector2f pos)
: PowerUp(sf::Color::Yellow, pos) {}

void AmmoPowerUp::applyEffect(class Spaceship *ship) {
    ship->updateStatistics(Spaceship::AmmoCount, ship->getStatistics(Spaceship::AmmoCount) + strength);
}