#ifndef ENDINGSCREEN_H
#define ENDINGSCREEN_H

#include <string>
#include <map>

#include "screen.h"
#include "team.h"

class EndingScreen : public Screen {
public:
    EndingScreen(sf::RenderWindow& window, ScreenHolder& screen_holder, Team *winning_team);

    bool input(sf::Event event);
    bool draw();
private:
    TextBox winning_message;
    TextBox team_name;
    TextBox to_menu;
};

#endif