#ifndef SCREENQUEUE_H
#define SCREENQUEUE_H

#include <vector>

#include "screen.h"
#include "delayedContainer.h"

class ScreenHolder {
public:
    void input(sf::Event event);
    void update(sf::Time dt);
    void draw();

    void push_back(Screen *screen);
    void pop_back();
    void clear();
    bool isEmpty();
    void applyChanges();

private:
    DelayedContainer<Screen> screens;
    bool modified;
};

#endif