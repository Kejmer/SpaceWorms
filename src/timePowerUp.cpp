#include "../include/timePowerUp.h"
#include "../include/world.h"

TimePowerUp::TimePowerUp(sf::Vector2f pos)
: PowerUp(sf::Color::Blue, pos) {
	texture.loadFromFile("assets/time_bonus.png"); // Może rzucić failem, jeśli nie załaduje obrazka, wtedy ładuje biały trójkąt. 
}

void TimePowerUp::applyEffect(class Spaceship *ship) {
    ship->getWorld()->extendTurn(sf::seconds(strength_in_s));
}