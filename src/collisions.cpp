#include "../include/collisions.h"
#include "../include/world.h"
#include "../include/spaceship.h"
#include "../include/powerUp.h"

inline void swap(Entity **first, Entity **second) {
    auto tmp = *first;
    *first = *second;
    *second = tmp;
}

inline bool checkRelation(Entity **entity1, Entity **entity2, Entity::CollisionCategory category1, Entity::CollisionCategory category2) {
    if ((*entity1)->getCategory() == category1 && (*entity2)->getCategory() == category2)
        return true;
    
    if ((*entity1)->getCategory() == category2 && (*entity2)->getCategory() == category1) {
        swap(entity1, entity2);
        return true;
    }

    return false;
}

inline bool checkAny(Entity **entity1, Entity **entity2, Entity::CollisionCategory category) {
    if ((*entity1)->getCategory() == category)
        return true;
    
    if ((*entity2)->getCategory() == category) {
        swap(entity1, entity2);
        return true;
    }

    return false;
}

void collide(Entity* first, Entity* second) {
    if (checkAny(&first, &second, Entity::None))
        return;

    if (checkAny(&first, &second, Entity::Hole))
        if (second->getCategory() != Entity::Hole && second->getCategory() != Entity::Spaceship)
            second->despawn();

    if (checkRelation(&first, &second, Entity::Bullet, Entity::Bullet)) {
        first->despawn();
        second->despawn();
    }

    if (checkRelation(&first, &second, Entity::Spaceship, Entity::Bullet)) {
        auto ship = (Spaceship*)first;
        float health = ship->getStatistics(Spaceship::Healthpoints);
        health -= 10;

        if (health <= 0)
            ship->despawn();
        else
            ship->updateStatistics(Spaceship::Healthpoints, health);

        second->despawn();
    }

    if (checkRelation(&first, &second, Entity::Spaceship, Entity::PowerUp)) {
        PowerUp *powUp = (PowerUp *) first;
        Spaceship *ship = (Spaceship *) second;
        powUp->applyEffect(ship);
    }
}