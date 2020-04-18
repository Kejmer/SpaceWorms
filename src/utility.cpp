#include <cmath>
#include "../include/utility.h"

float toRadian(float angle) {
    return M_PI / 180. * angle;
}

float toDegrees(float angle) {
    return 180. / M_PI * angle;
}

float calcDistance(sf::Vector2f a, sf::Vector2f b) {
	float distX = a.x - b.x;
    float distY = a.y - b.y;
    return std::sqrt(distX * distX + distY * distY);
}