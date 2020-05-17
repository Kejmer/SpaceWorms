#include "../include/selectable.h"

Selectable::Selectable()
: is_selected(false)
, is_default(true)
, is_enabled(true)
, destinations() {}

void Selectable::input(sf::Event event) {}

void Selectable::update(sf::Time dt) {}

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

void Selectable::setIfEnabled(bool value) {
    is_enabled = value;
}

bool Selectable::isEnabled() {
    return is_enabled;
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
    Selectable *result;

    do {
        if(destinations.count(key) == 0)
            return nullptr;

        result = destinations[key];
    }
    while (!result->isEnabled());

    return result;
}