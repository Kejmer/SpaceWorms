#include "../include/textBox.h"
#include "../include/utility.h"
#include "../include/entity.h"

TextBox::TextBox(Entity *entity, const sf::String &string, const sf::Font &font, sf::Vector2f position, unsigned int characterSize)
: Attachable(entity)
, font(font)
, string(string)
, text() {
    text = std::shared_ptr<sf::Text>{new sf::Text{this->string, this->font, characterSize}};
    text->setPosition(position);
    centerOrigin(*text);
}

TextBox::TextBox(Entity *entity, const sf::String &string, sf::Vector2f position, unsigned int characterSize)
: Attachable(entity)
, font()
, string(string)
, text() {
    sf::Font font;
    font.loadFromFile("assets/cour.ttf");
    this->font = font;
    text = std::shared_ptr<sf::Text>{new sf::Text{this->string, this->font, characterSize}};
    text->setPosition(position);
    centerOrigin(*text);
}

void TextBox::draw(sf::RenderWindow &window) {
    sf::Vector2f pos = text->getPosition();

    if (entity != nullptr)
        text->move(entity->getPosition());
    centerOrigin(*text);
    window.draw(*text);
    text->setPosition(pos);
}

void TextBox::updateString(const sf::String &string) {
    this->string = string;
    text->setString(this->string);
}