#ifndef AMMOPOWERUP_H
#define AMMOPOWERUP_H

#include "entity.h"
#include "spaceship.h"
#include "powerUp.h"

class AmmoPowerUp : public PowerUp {
public:
    AmmoPowerUp(sf::Vector2f pos);

    void applyEffect(class Spaceship *ship);
private:
	int strength = 10;
};

#endif // AMMOPOWERUP_H