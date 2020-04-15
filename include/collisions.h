#ifndef COLLISIONS_H
#define COLLISIONS_H

#include "entity.h"

inline bool checkRelation(Entity **entity1, Entity **entity2, Entity::CollisionCategory category1, Entity::CollisionCategory category2);
inline bool checkAny(Entity **entity1, Entity **entity2, Entity::CollisionCategory category);
void collide(Entity* first, Entity* second);

#endif