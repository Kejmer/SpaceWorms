#include "../include/buttonHolder.h"
#include "../include/button.h"

ButtonHolder::ButtonHolder()
: buttons()
, current_button(-1) {}

void ButtonHolder::input(sf::Event event) {
    if (current_button == -1)
        return;

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::W)
            moveCurrentPosition(-1);
        else if (event.key.code == sf::Keyboard::S)
            moveCurrentPosition(1);
        else if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space)
            buttons[current_button]->activate();
    }
}

void ButtonHolder::update(sf::Time dt) {}

void ButtonHolder::draw(sf::RenderWindow& window) {
    for (auto& button : buttons)
        button->draw(window);
}

void ButtonHolder::addButton(Button *button) {
    buttons.push_back(std::shared_ptr<Button>(button));

    if (current_button == -1) {
        current_button = 0;
        buttons[0]->select();
    }
}

void ButtonHolder::changeSelectedButton(int new_button) {
    buttons[current_button]->deselect();
    current_button = new_button;
    buttons[current_button]->select();
}

void ButtonHolder::moveCurrentPosition(int move) {
    int new_button = current_button + move;
    int nr_of_buttons = buttons.size();
    new_button %= nr_of_buttons;
    if (new_button < 0)
        new_button += nr_of_buttons;

    changeSelectedButton(new_button);
}