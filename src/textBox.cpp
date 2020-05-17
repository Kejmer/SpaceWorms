#include "../include/textBox.h"
#include "../include/utility.h"
#include "../include/entity.h"

TextBox::TextBox(Entity *entity, const sf::String &string, const sf::Font &font, sf::Vector2f position, unsigned int characterSize)
: Attachable(entity)
, font(font)
, background(sf::Color::Transparent)
, string(string.toUtf32())
, text() {
    text = std::shared_ptr<sf::Text>{new sf::Text{this->string, this->font, characterSize}};
    text->setPosition(position);
    centerOrigin(*text);
}

TextBox::TextBox(Entity *entity, const sf::String &string, sf::Vector2f position, unsigned int characterSize)
: Attachable(entity)
, font()
, background(sf::Color::Transparent)
, string(string.toUtf32())
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
    sf::RectangleShape backgroundRect;

    backgroundRect.setSize(text->getLocalBounds().getSize() + sf::Vector2f{10, 10});
    backgroundRect.setFillColor(background);
    backgroundRect.setPosition(text->getPosition());
    centerOrigin(backgroundRect);

    window.draw(backgroundRect);
    window.draw(*text);
    text->setPosition(pos);
}

void TextBox::updateString(const sf::String &string) {
    this->string = string.toUtf32();
    text->setString(this->string);
}

void TextBox::setColor(sf::Color color) {
    text->setFillColor(color);
}

void TextBox::setFont(sf::Font font) {
    this->font = font;
    text->setFont(font);
}

void TextBox::setFont(std::string font_path) {
    font.loadFromFile(font_path);
    text->setFont(font);
}

void TextBox::setSize(unsigned int size) {
    text->setCharacterSize(size);
}

void TextBox::setPosition(sf::Vector2f position) {
    text->setPosition(position);
}

void TextBox::setBackground(sf::Color color) {
    background = color;
}