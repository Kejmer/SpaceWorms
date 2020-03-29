#include "../include/circle.h"
#include "../include/utility.h"

Circle::Circle(sf::Vector2f position, float radius, sf::Color color)
: Entity(position)
, circle() {
    circle.setRadius(radius);
    circle.setPosition(position);
    circle.setFillColor(color);

    centerOrigin(circle);
}

void Circle::input(sf::Event event) {}

void Circle::update(sf::Time dt) {}

void Circle::draw(sf::RenderWindow& window) {
    window.draw(circle);
}