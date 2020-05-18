#include "screen.h"
#include "buttonHolder.h"

class WeaponPicker : public Screen {
public:
  WeaponPicker(sf::RenderWindow& window, ScreenHolder& screen_holder);

  bool update(sf::Time dt);
  bool draw();

private:
  void initButtons();

  ButtonHolder button_holder;
}