#include "../include/screenHolder.h"

void ScreenHolder::input(sf::Event event) {
    for (auto it = screens.end() - 1; it >= screens.begin() && !modified; it--)
        if (!(*it)->input(event) || modified)
            break;
}

void ScreenHolder::update(sf::Time dt) {
    for (auto it = screens.end() - 1; it >= screens.begin() && !modified; it--)
        if (!(*it)->update(dt) || modified)
            break;
}

void ScreenHolder::draw() {
    auto it = screens.end() - 1;
    for (; it >= screens.begin() && !modified; it--)
        if (!(*it)->draw() || modified)
            break;
    for (; it != screens.end(); it++)
        (*it)->draw();
}

void ScreenHolder::push_back(Screen *screen) {
    screens.add(screen);
    modified = true;
}

void ScreenHolder::pop_back() {
    screens.pop_back();
    modified = true;
}

void ScreenHolder::clear() {
    screens.clear();
    modified = true;
}

bool ScreenHolder::isEmpty() {
    return screens.empty();
}

void ScreenHolder::applyChanges() {
    modified = false;
    screens.applyPendingChanges();
}