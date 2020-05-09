#ifndef SCREEN_H
#define SCREEN_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "entity.h"
#include "delayedContainer.h"

// Forward declaration
class ScreenHolder;

class Screen {
public:
    Screen(sf::RenderWindow& window, ScreenHolder& screen_holder);
    virtual ~Screen() = default;

    virtual bool input(sf::Event event);
    virtual bool update(sf::Time dt);
    virtual bool draw();

    virtual std::shared_ptr<Entity> addEntity(Entity* entity);
    virtual void addEntity(std::shared_ptr<Entity> entity);
    virtual void removeEntity(Entity* entity);

protected:
    sf::RenderWindow& window;
    ScreenHolder& screen_holder;
    DelayedContainer<Entity> entities;
};

#endif