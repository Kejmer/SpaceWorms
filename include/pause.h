#ifndef PAUSE_H
#define PAUSE_H

#include "screen.h"
#include "buttonHolder.h"
#include "textBox.h"


class Pause : public Screen {
public:
    Pause(sf::RenderWindow& window, ScreenHolder& screen_holder);

    bool input(sf::Event event);
    bool update(sf::Time dt);
    bool draw();
  
private:
    sf::RectangleShape background;
    ButtonHolder buttons;
    TextBox title;
};

#endif /* PAUSE_H */