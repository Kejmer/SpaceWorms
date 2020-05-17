#ifndef MAINMENU_H
#define MAINMENU_H

#include "screen.h"
#include "buttonHolder.h"
#include "textBox.h"

class MainMenu : public Screen {
public:
    MainMenu(sf::RenderWindow& window, ScreenHolder& screen_holder);

    bool input(sf::Event event);
    bool update(sf::Time dt);
    bool draw();

private:
    void initButtons();
    void initAttachables();

    ButtonHolder button_holder;
    std::vector<std::shared_ptr<Attachable>> attachables;
};

#endif