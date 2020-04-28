#include "../include/powerUp.h"
#include "../include/boundingHitbox.h"

PowerUp::PowerUp(sf::Color col, sf::Vector2f pos) 
: Entity(pos, Entity::PowerUp)
, color(col)
, shape (sf::RectangleShape {}) {
    shape.setPosition(pos);
    shape.setSize(size);
    shape.setFillColor(color);

    hitbox = std::unique_ptr<BoundingHitbox>(new BoundingHitbox{this, &shape});
}

void PowerUp::input(sf::Event event) {}

void PowerUp::update(sf::Time dt) {}

void PowerUp::draw(sf::RenderWindow& window) {
	window.draw(shape);
}