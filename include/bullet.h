#ifndef BULLET_H
#define BULLET_H

#include "entity.h"

class AbsBullet : public Entity {
public:
    AbsBullet(sf::Vector2f position, sf::Vector2f velocity, float bullet_size);
    void input(sf::Event event);
    void draw(sf::RenderWindow& window);
protected:
    void spawn();

    sf::CircleShape bullet;
    sf::Vector2f velocity;
    sf::Time last_spawn;
    static const sf::Time spawn_delay;
};

class SimpleBullet : public AbsBullet {
public:
    SimpleBullet(sf::Vector2f position, sf::Vector2f velocity);
    void update(sf::Time dt);
};

class SplitBullet : public AbsBullet {
public:
    SplitBullet(sf::Vector2f position, sf::Vector2f velocity);
    void update(sf::Time dt);
private:
    // static const sf::Time split_delay;
    // sf::spawn life_span;
};

#endif /* BULLET_H */