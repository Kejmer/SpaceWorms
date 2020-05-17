#ifndef SETTINGS_H
#define SETTINGS_H

#include <vector>

#include "screen.h"
#include "buttonHolder.h"
#include "textBox.h"

class TeamOptionField : public ButtonHolder {
public:
    TeamOptionField(ButtonHolder& button_holder, sf::Vector2f size, sf::Vector2f position, sf::Color team_color, int team_nr, std::vector<int>& ship_counts);

    void input(sf::Event event);
    void update(sf::Time dt);
    void draw(sf::RenderWindow& window);

    void activate();
private:
    static const sf::Color background_color;
    static const sf::Color selection_color;
    static const int max_ships;

    void initButtons();

    ButtonHolder& button_holder;
    sf::Color team_color;
    int team_nr;
    std::vector<int>& ship_counts;
    int nr_of_ships;
    sf::RectangleShape background;
    sf::RectangleShape team_indicator;
    TextBox ships_nr;
    TextBox ships;
    ButtonHolder buttons; 
    bool has_focus;
};

class Settings : public Screen {
public:
    Settings(sf::RenderWindow& window, ScreenHolder& screen_holder, std::vector<int>& ship_counts);

    bool input(sf::Event event);
    bool update(sf::Time dt);
    bool draw();

private:
    std::vector<int>& ship_counts;
    std::vector<TeamOptionField> teams;
    ButtonHolder buttons;
};

#endif