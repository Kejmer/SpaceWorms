#include <cmath>
#include "../include/utility.h"

void centerOrigin(sf::Shape& shape) {
    sf::FloatRect bounds = shape.getLocalBounds();
    shape.setOrigin(std::floor(bounds.left + bounds.width / 2.), 
                    std::floor(bounds.top + bounds.height / 2.));
}

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