#ifndef BAR_H
#define BAR_H

#include <SFML/Graphics.hpp>

#include "attachable.h"

class Bar : public Attachable {
public:
    Bar(Entity *entity, sf::Color leftColor, sf::Color rightColor, sf::Vector2f dimensions, 
        sf::Vector2f position, float max_value, float default_value = -1);
    Bar(Entity *entity, sf::Color leftColor, sf::Color rightColor, sf::RectangleShape shape,
        float max_value, float default_value = -1);

    void draw(sf::RenderWindow &window);

    float getValue();
    void setValue(float new_value);
    
    float getMaxValue();
    void setMaxValue(float max_value);

    sf::RectangleShape getRectangle();
    void changeRectangle(sf::Vector2f new_dimensions);
    void changeRectangle(sf::Vector2f new_dimensions, sf::Vector2f new_position);
    void changeRectangle(sf::RectangleShape new_rectangle);
private:
    sf::RectangleShape rectangle;
    sf::Color left_color;
    sf::Color right_color;
    float current_value;
    float max_value;
};

#endif