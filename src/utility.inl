#include <cmath>

template<typename T>
void centerOrigin(T& shape) {
    sf::FloatRect bounds = shape.getLocalBounds();
    shape.setOrigin(std::floor(bounds.left + bounds.width / 2.), 
                    std::floor(bounds.top + bounds.height / 2.));
}