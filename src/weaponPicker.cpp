#include "../include/weaponPicker.h"
#include "../include/defines.h"
#include "../include/world.h"
#include "../include/screenHolder.h"
#include "../include/button.h"

WeaponPicker::WeaponPicker(sf::RenderWindow& window, ScreenHolder& screen_holder, World *world)
: Screen(window, screen_holder)
, world(world)
, current_pick(world->currentWeapon())
, button_holder() {
  initButtons();
}

bool WeaponPicker::input(sf::Event event) {
  button_holder.input(event);
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Escape)
      cancel();
  }
  return false;
}

bool WeaponPicker::update(sf::Time dt) {
  button_holder.update(dt);
  return false;
}

bool WeaponPicker::draw() {
  button_holder.draw(window);
  return true;
}

void WeaponPicker::confirm() {
  world->setCurrentWeapon(current_pick);
  cancel();
}

void WeaponPicker::cancel() {
  screen_holder.pop_back();
}

void WeaponPicker::initButtons() {
  Button *btns[FACTORIES_COUNT];
  float position = 100;
  for (int i = 0; i < FACTORIES_COUNT; i++) {
    btns[i] = new Button(button_holder, {800, position}, {120, 120}, sf::Color(119, 131, 153), sf::Color::Blue);
    btns[i]->assignAction(createAction(i));
    position += 130;
  }
  btns[0]->setText(L"SIMPLE");
  btns[1]->setText(L"SPLIT");

  for (int i = 0; i < FACTORIES_COUNT; i++) {
    button_holder.addButton(btns[i]);
  }
}

std::function<void()> WeaponPicker::createAction(int weapon_number) {
  return [=]() {
    current_pick = weapon_number;
    confirm();
  };
}


// void WeaponPicker::next() {
//   current_pick++;
//   current_pick %= FACTORIES_COUNT;
// }

// void WeaponPicker::previous() {
//   current_pick--;
//   current_pick %= FACTORIES_COUNT;
// }