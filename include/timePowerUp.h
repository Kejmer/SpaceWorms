#ifndef TIMEPOWERUP_H
#define TIMEPOWERUP_H

#include "entity.h"
#include "spaceship.h"
#include "powerUp.h"

class TimePowerUp : public PowerUp {
public:
    TimePowerUp(sf::Vector2f pos);

    void applyEffect(class Spaceship *ship);
private:
	float strength_in_s = 1;
};

#endif // TIMEPOWERUP_H