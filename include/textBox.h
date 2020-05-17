#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <memory>

#include "attachable.h"

class TextBox : public Attachable {
public:
    TextBox(Entity *entity, const sf::String &string, const sf::Font &font, sf::Vector2f position = {0, 0}, unsigned int characterSize = 30);
    TextBox(Entity *entity, const sf::String &string, sf::Vector2f position = {0, 0}, unsigned int characterSize = 30);

    void draw(sf::RenderWindow &window);
    void updateString(const sf::String &string);
    void setColor(sf::Color color);
    void setFont(sf::Font font);
    void setFont(std::string font_path);
    void setSize(unsigned int size);
    void setPosition(sf::Vector2f position);
    void setBackground(sf::RectangleShape rectangle);
private:
    sf::Font font;
    sf::RectangleShape background;
    std::basic_string<sf::Uint32> string;
    std::shared_ptr<sf::Text> text;
}; 

#endif