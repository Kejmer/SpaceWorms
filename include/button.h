#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>
#include <functional>

#include "buttonHolder.h"
#include "textBox.h"

class Button {
public:
    Button(ButtonHolder& button_holder, sf::Vector2f position, sf::Vector2f size, sf::Color not_selected, sf::Color selected);

    void draw(sf::RenderWindow &window);

    void setText(sf::String text);
    void setTextColor(sf::Color color);
    void setTextSize(unsigned int size);
    void setTextFont(sf::Font font);
    void setTextFont(std::string font_path);

    void select();
    void deselect();

    void assignAction(std::function<void()> action);
    void activate();
private:
    ButtonHolder& button_holder;
    sf::RectangleShape button;
    TextBox text;
    sf::Color not_selected;
    sf::Color selected;
    std::function<void()> action;
    bool is_selected;
};

#endif