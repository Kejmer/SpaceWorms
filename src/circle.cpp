#include "../include/circle.h"

#include <cmath>

Circle::Circle(sf::Vector2f position, float radius, sf::Color color)
: Entity(position)
, circle() {
    circle.setRadius(radius);
    circle.setPosition(position);
    circle.setFillColor(color);

    sf::FloatRect bounds = circle.getLocalBounds();
    circle.setOrigin(std::floor(bounds.left + bounds.width / 2.), 
                     std::floor(bounds.top + bounds.height / 2.));
}

void Circle::input(sf::Event event) {}

void Circle::update(sf::Time dt) {}

void Circle::draw(sf::RenderWindow& window) {
    window.draw(circle);
}