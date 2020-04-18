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
private:
    sf::Font font;
    sf::String string;
    std::shared_ptr<sf::Text> text;
}; 

#endif