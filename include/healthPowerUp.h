#ifndef HEALTHPOWERUP_H
#define HEALTHPOWERUP_H

#include "entity.h"
#include "spaceship.h"
#include "powerUp.h"

class HealthPowerUp : public PowerUp {
public:
    HealthPowerUp(sf::Vector2f pos);

    void applyEffect(class Spaceship *ship);
private:
	int strength = 25;
};

#endif // HEALTHPOWERUP_H