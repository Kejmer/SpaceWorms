#ifndef BUTTONHOLDER_H
#define BUTTONHOLDER_H

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "selectable.h"

// Forward declaration
class Button;

class ButtonHolder : public Selectable {
public:
    ButtonHolder();
    virtual ~ButtonHolder() = default;

    virtual void input(sf::Event event);
    virtual void update(sf::Time dt);
    virtual void draw(sf::RenderWindow& window);

    void addButton(Button *button);
    void addSelectable(Selectable *selectable);

    void registerNewDestination(Selectable *selectable, sf::Keyboard::Key key, Selectable *destination);
    void removeAllDestinations(Selectable *selectable);
    void removeDestination(Selectable *selectable, sf::Keyboard::Key key);
    void setDefaultDestinations(Selectable *selectable);

    void interceptInput(Selectable *interceptor);
    void stopInputForwarding();
protected:
    void changeSelection(Selectable *selectable);
    void moveCurrentPosition(sf::Keyboard::Key key);
    int findSelectable(Selectable *selectable);

    std::vector<std::shared_ptr<Selectable>> selectables;
    int current_selection;
    Selectable *input_interceptor;
};

#endif