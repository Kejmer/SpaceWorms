#ifndef SELECTABLE_H
#define SELECTABLE_H

#include <SFML/Graphics.hpp>
#include <map>

class Selectable {
public:
    Selectable();
    virtual ~Selectable() = default;

    virtual void input(sf::Event event);
    virtual void draw(sf::RenderWindow &window) = 0;

    virtual void select();
    virtual void deselect();
    virtual void activate();

    void setIfDefault(bool value);
    bool isDefault();

    void registerNewDestination(sf::Keyboard::Key key, Selectable *destination);
    void removeAllDestinations();
    void removeDestination(sf::Keyboard::Key key);
    Selectable *getNextSelectable(sf::Keyboard::Key key);
protected:
    bool is_selected;
    bool is_default;

    std::map<sf::Keyboard::Key, Selectable*> destinations;
};

#endif