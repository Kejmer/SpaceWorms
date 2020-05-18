#include "../include/ammoPowerUp.h"

AmmoPowerUp::AmmoPowerUp(sf::Vector2f pos)
: PowerUp(sf::Color::Yellow, pos) {
	texture.loadFromFile("assets/ammo_bonus.png"); // Może rzucić failem, jeśli nie załaduje obrazka, wtedy ładuje biały trójkąt. 
	shape.setTexture(&texture, false);

}

void AmmoPowerUp::applyEffect(class Spaceship *ship) {
    ship->updateStatistics(Spaceship::AmmoCount, ship->getStatistics(Spaceship::AmmoCount) + strength);
}