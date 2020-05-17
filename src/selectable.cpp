#include "../include/selectable.h"

Selectable::Selectable()
: is_selected(false)
, is_default(true)
, destinations() {}

void Selectable::input(sf::Event event) {}

void Selectable::select() {
    is_selected = true;
}

void Selectable::deselect() {
    is_selected = false;
}

void Selectable::activate() {}

void Selectable::setIfDefault(bool value) {
    is_default = value;
}

bool Selectable::isDefault() {
    return is_default;
}

void Selectable::registerNewDestination(sf::Keyboard::Key key, Selectable *destination) {
    destinations[key] = destination;
}

void Selectable::removeAllDestinations() {
    destinations.clear();
}

void Selectable::removeDestination(sf::Keyboard::Key key) {
    destinations.erase(key);
}

Selectable *Selectable::getNextSelectable(sf::Keyboard::Key key) {
    if(destinations.count(key) == 0)
        return nullptr;

    return destinations[key];
}