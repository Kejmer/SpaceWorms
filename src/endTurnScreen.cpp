#include <cmath>
#include "../include/endTurnScreen.h"
#include "../include/screenHolder.h"
#include "../include/textBox.h"
#include "../include/utility.h"

EndTurnScreen::EndTurnScreen(sf::RenderWindow& window, ScreenHolder& screen_holder)
: Screen(window, screen_holder)
, timeLeft(sf::seconds(3.f))
, background(sf::RectangleShape())
, top_text(TextBox(nullptr, "Koniec tury", {0, 0}, 12))
, bottom_text(nullptr, "Nastepna tura za: 3s", {0, 0}, 12) {
    sf::Vector2f middleOfScreen = sf::Vector2f(window.getSize() / 2u);
    background.setSize(sf::Vector2f(window.getSize()) * 0.67f);
    centerOrigin(background);
    background.setPosition(middleOfScreen);
    background.setFillColor(sf::Color::Black);
    sf::Vector2f temp(0, -25);
    top_text.setPosition(middleOfScreen + temp);
    top_text.setColor(sf::Color::White);
    temp.y = 25.f;
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
    bottom_text.updateString("Nastepna tura za: " + std::to_string(secondsLeft) + "s");
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) || timeLeft <= sf::Time()) {
      screen_holder.pop_back();
    }
    return false;
}