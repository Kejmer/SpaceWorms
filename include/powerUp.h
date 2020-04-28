#ifndef POWERUP_H
#define POWERUP_H

#include "entity.h"
#include "spaceship.h"

class PowerUp : public Entity {
public:
    enum PowerUpType {
        Health,
        Time,
        Ammo
    };

    PowerUp(sf::Color color, sf::Vector2f pos);
    virtual ~PowerUp() = default;
    
    void input(sf::Event event);
    void update(sf::Time dt);
    void draw(sf::RenderWindow& window);

    virtual void applyEffect(class Spaceship *ship) = 0;

private:
    sf::Color color;
    sf::RectangleShape shape;
    sf::Vector2f size = {25, 25};
};

#endif // POWERUP_H
