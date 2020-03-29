#ifndef UTILITY_H
#define UTILITY_H

#include <SFML/Graphics.hpp>
#include <cmath>

const float eps = 1e-6;

void centerOrigin(sf::Shape& shape);

float toRadian(float angle);
float toDegrees(float angle);
float calcDistance(sf::Vector2f a, sf::Vector2f b);

#endif