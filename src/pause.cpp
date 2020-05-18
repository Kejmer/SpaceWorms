#include "../include/pause.h"
#include "../include/screenHolder.h"
#include "../include/button.h"
#include "../include/mainMenu.h"

Pause::Pause(sf::RenderWindow& window, ScreenHolder& screen_holder)
: Screen(window, screen_holder)
, background((sf::Vector2f)window.getSize())
, buttons()
, title(nullptr, "Pauza", {512, 134}, 60) {
  background.setFillColor(sf::Color(30,30,30,128));

  Button *resume = new Button(buttons, {512, 483}, {700, 50}, sf::Color(119, 131, 153), sf::Color::Blue);
  resume->setText(L"Wznów grę");
  resume->assignAction([this](){
    this->screen_holder.pop_back();
  });
  buttons.addButton(resume);

  Button *to_menu = new Button(buttons, {512, 543}, {700, 50}, sf::Color(119, 131, 153), sf::Color::Blue);
  to_menu->setText(L"Zakończ grę i wróć do menu");
  to_menu->assignAction([this](){
    this->screen_holder.clear();
    this->screen_holder.push_back(new MainMenu(this->window, this->screen_holder));
  });
  buttons.addButton(to_menu);
}

bool Pause::input(sf::Event event) {
  buttons.input(event);
  return false;
}

bool Pause::draw() {
  window.draw(background);
  title.draw(window);
  buttons.draw(window);
  return true;
}

bool Pause::update(sf::Time dt) {
  buttons.update(dt);
  return false;
}