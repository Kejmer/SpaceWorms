#ifndef BUTTONHOLDER_H
#define BUTTONHOLDER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

// Forward declaration
class Button;

class ButtonHolder {
public:
    ButtonHolder();

    void input(sf::Event event);
    void update(sf::Time dt);
    void draw(sf::RenderWindow& window);

    void addButton(Button *button);
private:
    void changeSelectedButton(int new_button);
    void moveCurrentPosition(int move);

    std::vector<std::shared_ptr<Button>> buttons;
    int current_button;
};

#endif