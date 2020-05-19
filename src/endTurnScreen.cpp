#include <cmath>
#include "../include/endTurnScreen.h"
#include "../include/screenHolder.h"
#include "../include/textBox.h"
#include "../include/utility.h"

EndTurnScreen::EndTurnScreen(sf::RenderWindow& window, ScreenHolder& screen_holder, std::shared_ptr<Team> team)
: Screen(window, screen_holder)
, timeLeft(sf::seconds(3.f))
, background(sf::RectangleShape())
, top_text(TextBox(nullptr, "Koniec tury", {0, 0}, 15))
, bottom_text(nullptr, L"Następna tura za: 3s", {0, 0}, 15)
, next_team(team) {
    sf::Vector2f middleOfScreen = sf::Vector2f(window.getSize() / 2u);
    sf::Vector2f temp(middleOfScreen.x * 0.6f, middleOfScreen.y * 0.35f);
    background.setSize(temp);
    centerOrigin(background);
    background.setPosition(middleOfScreen);
    background.setFillColor(sf::Color::Black);
    temp.x = 0;
    temp.y = -25;
    top_text.setPosition(middleOfScreen + temp);
    top_text.setColor(sf::Color::White);
    temp.y = 25;
    bottom_text.setPosition(middleOfScreen + temp);
    bottom_text.setColor(sf::Color::White);
}

bool EndTurnScreen::draw() {
    window.draw(background);
    top_text.draw(window);
    bottom_text.draw(window);
    return true;
}

bool EndTurnScreen::update(sf::Time dt) {
    timeLeft -= dt;
    int secondsLeft = static_cast<int>(std::ceil(timeLeft.asSeconds()));
    sf::Color next_team_color = next_team->getColor();
    std::wstring team_string;
    if (next_team_color == sf::Color::Red)
        team_string = L"czerwonej";
    else if (next_team_color == sf::Color::Blue)
        team_string = L"niebieskiej";
    else if (next_team_color == sf::Color::Green)
        team_string = L"zielonej";
    else if (next_team_color == sf::Color::Yellow)
        team_string = L"żółtej";
    else
        team_string = L"szarej";
    bottom_text.updateString(L"Tura drużyny " + team_string + L" za: " +
        std::to_wstring(secondsLeft) + L"s");
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || timeLeft <= sf::Time()) {
      screen_holder.pop_back();
    }
    return false;
}