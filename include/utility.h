#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/Graphics.hpp>
#include <cmath>

const float eps = 1e-6;

template<typename T>
void centerOrigin(T& shape);

float toRadian(float angle);
float toDegrees(float angle);
float calcDistance(sf::Vector2f a, sf::Vector2f b);

#include "../src/utility.inl"

#endif