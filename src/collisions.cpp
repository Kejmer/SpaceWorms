#include <algorithm>

#include "../include/collisions.h"

inline bool checkRelation(Entity* entity1, Entity* entity2, Entity::CollisionCategory category1, Entity::CollisionCategory category2) {
    return (entity1->getCategory() == category1 && entity2->getCategory() == category2) ||
           (entity1->getCategory() == category2 && entity2->getCategory() == category1);
}

inline bool checkAny(Entity* entity1, Entity* entity2, Entity::CollisionCategory category) {
    return (entity1->getCategory() == category || entity2->getCategory() == category);
}

void collide(Entity* first, Entity* second) {
    if(checkAny(first, second, Entity::None))
        return;
}