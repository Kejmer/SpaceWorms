#include "../include/button.h"
#include "../include/utility.h"

Button::Button(ButtonHolder& button_holder, sf::Vector2f position, sf::Vector2f size, sf::Color not_selected, sf::Color selected) 
: button_holder(button_holder)
, button(size)
, text(nullptr, "", position)
, not_selected(not_selected)
, selected(selected)
, action([](){})
, is_selected(false) {
    centerOrigin(button);
    button.setPosition(position);
    button.setFillColor(not_selected);
}

void Button::draw(sf::RenderWindow &window) {
    if (is_selected)
        button.setFillColor(selected);
    else
        button.setFillColor(not_selected);
        
    window.draw(button);
    text.draw(window);
}

void Button::setText(std::string text) {
    this->text.updateString(text);
}

void Button::setTextColor(sf::Color color) {
    text.setColor(color);
}

void Button::setTextSize(unsigned int size) {
    text.setSize(size);
}

void Button::setTextFont(sf::Font font) {
    text.setFont(font);
}

void Button::setTextFont(std::string font_path) {
    text.setFont(font_path);
}

void Button::select() {
    is_selected = true;
}

void Button::deselect() {
    is_selected = false;
}

void Button::assignAction(std::function<void()> action) {
    this->action = action;
}

void Button::activate() {
    action();
}