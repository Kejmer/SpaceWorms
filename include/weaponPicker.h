#ifndef WEAPON_PICKER_H
#define WEAPON_PICKER_H

#include <functional>

#include "screen.h"
#include "buttonHolder.h"

class World;

class WeaponPicker : public Screen {
public:
  WeaponPicker(sf::RenderWindow& window, ScreenHolder& screen_holder, World *world);

  bool input(sf::Event event);
  bool update(sf::Time dt);
  bool draw();

private:
  void confirm();
  void cancel();
  void initButtons();
  std::function<void()> createAction(int weapon_number);


  World *world;
  int current_pick;

  ButtonHolder button_holder;
};

#endif /* WEAPON_PICKER_H */