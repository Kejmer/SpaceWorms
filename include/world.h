#ifndef WORLD_H
#define WORLD_H

#include "entity.h"
#include "hole.h"

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
    void addHoleEntity(GHole *hole);
    void removeEntity(Entity* entity);
    sf::Vector2f calcGravAccel(sf::Vector2f pos);

    bool isTimeFlowing();
private:
    enum Action {
        Add,
        Remove
    };

    struct Change {
        Action action;
        Entity* entity;
    };

    void applyPendingChanges();
    
    sf::RenderWindow& window;
    std::vector<std::unique_ptr<Entity>> entities;
    std::vector<GHole*> holeEntities; //póki nie chcemy usuwać czarnych dziur to będzie działać
    std::vector<Change> pending_changes;

    static const sf::Time frame_time;

    bool is_time_flowing;
    float gravity_multiplier = 9;
};

#endif