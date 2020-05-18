#include <SFML/Graphics.hpp>

#include "../include/endingScreen.h"
#include "../include/screenHolder.h"
#include "../include/mainMenu.h"

EndingScreen::EndingScreen(sf::RenderWindow& window, ScreenHolder& screen_holder, Team *winning_team)
: Screen(window, screen_holder)
, winning_message(nullptr, L"Wygrała drużyna", {512, 162}, 50)
, team_name(nullptr, "", {512, 222}, 50)
, to_menu(nullptr, L"Naciśnij ENTER aby wrócić do głównego menu", {512, 576}) {
    if (winning_team == nullptr) {
        winning_message.setPosition({512, 192});
        winning_message.updateString(L"Remis!");
    }
    else {
        sf::Color team_color = winning_team->getColor();
        if (team_color == sf::Color::Red)
            team_name.updateString(L"czerwonych");
        else if (team_color == sf::Color::Blue)
            team_name.updateString(L"niebieskich");
        else if (team_color == sf::Color::Green)
            team_name.updateString(L"zielonych");
        else if (team_color == sf::Color::Yellow)
            team_name.updateString(L"żółtych");
        else
            team_name.updateString(L"szarych");

        team_name.setColor(team_color);
    }
}

bool EndingScreen::input(sf::Event event) {
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Enter) {
        screen_holder.clear();
        screen_holder.push_back(new MainMenu(window, screen_holder));
    }

    return false;
}

bool EndingScreen::draw() {
    winning_message.draw(window);
    team_name.draw(window);
    to_menu.draw(window);

    return false;
}