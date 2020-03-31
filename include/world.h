#ifndef WORLD_H
#define WORLD_H

#include "entity.h"
#include "hole.h"
#include "delayedContainer.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class World {
public:
    World(sf::RenderWindow& window);
    void input();
    void update(sf::Time dt);
    void draw();
    void run();

    void addHoleEntity(GHole *hole);
    void removeHoleEntity(GHole *hole);

    std::shared_ptr<Entity> addEntity(Entity* entity);
    void addEntity(std::shared_ptr<Entity> entity);
    void removeEntity(Entity* entity);
    sf::Vector2f calcGravAccel(sf::Vector2f pos);

    bool isTimeFlowing();
private:
    sf::RenderWindow& window;
    DelayedContainer<GHole> holeEntities;
    DelayedContainer<Entity> entities;

    static const sf::Time frame_time;

    bool is_time_flowing;
    float gravity_multiplier = 900;
};

#endif