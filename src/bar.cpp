#include "../include/bar.h"
#include "../include/utility.h"
#include "../include/entity.h"

Bar::Bar(Entity *entity, sf::Color left_color, sf::Color right_color, sf::Vector2f dimensions, 
         sf::Vector2f position, float max_value, float default_value)
: Bar(entity, left_color, right_color, sf::RectangleShape{}, max_value, default_value) {
    changeRectangle(dimensions, position);
}

Bar::Bar(Entity *entity, sf::Color left_color, sf::Color right_color, sf::RectangleShape rectangle,
         float max_value, float default_value)
: Attachable(entity)
, rectangle(rectangle)
, left_color(left_color)
, right_color(right_color)
, current_value(default_value)
, max_value(max_value) {
    centerOrigin(rectangle);
}

void Bar::draw(sf::RenderWindow &window) {
    sf::RectangleShape left = rectangle;
    sf::Vector2f size = rectangle.getSize();
    left.setSize({current_value / max_value * size.x, size.y});

    if (entity != nullptr)
        left.setPosition(left.getPosition() + entity->getPosition());
    left.setFillColor(left_color);
    window.draw(left);

    sf::RectangleShape right = rectangle;
    right.setSize({(1 - current_value / max_value) * size.x, size.y});
    if (entity != nullptr)
        right.setPosition(right.getPosition() + entity->getPosition());
    right.setOrigin({-(left.getSize().x - size.x / 2), right.getOrigin().y});
    right.setFillColor(right_color);
    window.draw(right);
}

float Bar::getValue() {
    return current_value;
}

void Bar::setValue(float new_value) {
    current_value = new_value;
}
    
float Bar::getMaxValue() {
    return max_value;
}

void Bar::setMaxValue(float max_value) {
    this->max_value = max_value;
}

sf::RectangleShape Bar::getRectangle() {
    return rectangle;
}

void Bar::changeRectangle(sf::Vector2f new_dimensions) {
    rectangle.setSize(new_dimensions);
    centerOrigin(rectangle);
}

void Bar::changeRectangle(sf::Vector2f new_dimensions, sf::Vector2f new_position) {
    changeRectangle(new_dimensions);
    rectangle.setPosition(new_position);
}

void Bar::changeRectangle(sf::RectangleShape new_rectangle) {
    rectangle = new_rectangle;
    centerOrigin(rectangle);
}