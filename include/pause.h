#include "screen.h"


class Pause : public Screen {
public:
    Pause(sf::RenderWindow& window, ScreenHolder& screen_holder);

    bool update(sf::Time dt);
    bool draw();
};