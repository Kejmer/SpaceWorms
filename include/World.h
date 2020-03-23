#ifndef WORLD_H
#define WORLD_H

#include "Entity.h"

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

    void addEntity(Entity* entity);
    void removeEntity(Entity* entity);

    bool isTimeFlowing();
private:
    sf::RenderWindow& window;
    std::vector<std::unique_ptr<Entity>> entities;

    static const sf::Time frame_time;

    bool is_time_flowing;
};

#endif