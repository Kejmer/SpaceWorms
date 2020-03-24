#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

// Temporary class just for testing

// później ta klasa powinna dziedziczyć po jakimś abstrakcyjnym AbstrBullet SPRINT-2
// zamiast velocity dać Move SPRINT-1
class SimpleBullet : public Entity {
public:
    SimpleBullet(sf::Vector2f position, sf::Vector2f velocity);
    void input(sf::Event event);
    void update(sf::Time dt);
    void draw(sf::RenderWindow& window);
private:
    sf::CircleShape bullet;
    sf::Vector2f velocity;
};

#endif /* BULLET_H */