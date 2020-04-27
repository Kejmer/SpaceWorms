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
    void spawn();

    sf::CircleShape bullet;
    sf::Vector2f velocity;
    sf::Time last_spawn;
    static const sf::Time spawn_delay;
};

#endif /* BULLET_H */