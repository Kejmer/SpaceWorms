#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "hitbox.h"
#include "attachable.h"

// Forward declaration
class World;
class Screen;

class Entity {
public:
    enum CollisionCategory {
        Bullet,
        Hole,
        Spaceship,
        PowerUp,
        None
    };

    Entity(sf::Vector2f position, CollisionCategory category = None);
    virtual ~Entity() = default;
    virtual void input(sf::Event event) = 0;
    virtual void update(sf::Time dt) = 0;
    virtual void draw(sf::RenderWindow& window) = 0;

    void setPosition(sf::Vector2f position);
    sf::Vector2f getPosition();

    virtual void setWorld(World *world);
    World* getWorld();
    virtual void setScreen(Screen *screen);
    Screen* getScreen();
    void despawn();

    CollisionCategory getCategory() const;
    void setCategory(CollisionCategory category);

    bool doesCollide(Entity &entity);

    virtual sf::Transform getTransform() const;

    virtual void move(sf::Vector2f vector);

    void addAttachable(Attachable *att);
    void addAttachable(std::shared_ptr<Attachable> att);
    void removeAttachable(Attachable *att);

    int getDamage();
protected:
    CollisionCategory collision_category;

    int damage;
    bool isTimeFlowing();
    float distanceTo(sf::Vector2f where);
    sf::Vector2f position;
    World* world;
    Screen* screen;

    std::unique_ptr<Hitbox> hitbox;
    std::vector<std::shared_ptr<Attachable>> attachables_to_draw;
};

#endif
