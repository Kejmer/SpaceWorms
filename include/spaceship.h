#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "entity.h"

#include <SFML/Graphics.hpp>

class Spaceship : public Entity {
public:
    Spaceship(sf::Vector2f position);
    void input(sf::Event event);
    void update(sf::Time dt);
    void draw(sf::RenderWindow& window);

    void shoot();
    void move(sf::Vector2f vector);
private:
    void realtimeInput();
    sf::Vector2f getDirection();
    
    static const float rotation_speed;
    static const float shots_per_second;
    static const float bullet_speed;
    static const float ship_speed;

    sf::CircleShape ship;
    int rotation;
    float move_dir;

    sf::Time last_shot;
};

#endif