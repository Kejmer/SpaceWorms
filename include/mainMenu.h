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
    static const std::vector<sf::Color> team_colors;

    void initButtons();
    void initAttachables();
    void initTeams(World *world);

    ButtonHolder button_holder;
    std::vector<std::shared_ptr<Attachable>> attachables;
    std::vector<int> ship_counts;
};

#endif