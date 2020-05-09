#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <SFML/Graphics.hpp>

#include "screenHolder.h"

class ScreenManager {
public:
    ScreenManager(sf::RenderWindow& window);
    void run();

private:
    void draw();
    void input();
    void init();

    static const sf::Time frame_time;

    sf::RenderWindow& window;
    ScreenHolder screen_holder;
};

#endif