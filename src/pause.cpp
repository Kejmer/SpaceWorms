#include "../include/pause.h"
#include "../include/screenHolder.h"

Pause::Pause(sf::RenderWindow& window, ScreenHolder& screen_holder)
: Screen(window, screen_holder) {}

bool Pause::draw() {
  window.clear(sf::Color(30,30,30,128)); // Anita spróbuj zrobić aby menu pauzy było półprzezroczyste
  return true;
}

bool Pause::update(sf::Time dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
    screen_holder.pop_back();
  }
  return false;
}