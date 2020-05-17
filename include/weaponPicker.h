#include "screen.h"

class WeaponPicker : public Screen {
  WeaponPicker(sf::RenderWindow& window, ScreenHolder& screen_holder);

  bool update(sf::Time dt);
  bool draw();

}