#include "../include/buttonHolder.h"
#include "../include/button.h"

ButtonHolder::ButtonHolder()
: selectables()
, current_selection(-1)
, input_interceptor(nullptr) {}

void ButtonHolder::input(sf::Event event) {
    if (current_selection == -1)
        return;

    if (input_interceptor != nullptr) {
        input_interceptor->input(event);
        return;
    }

    if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Enter || event.key.code == sf::Keyboard::Space)
            selectables[current_selection]->activate();
        else
            moveCurrentPosition(event.key.code);
    }
}

void ButtonHolder::update(sf::Time dt) {}

void ButtonHolder::draw(sf::RenderWindow& window) {
    for (auto& selectable : selectables)
        selectable->draw(window);
}

void ButtonHolder::addButton(Button *button) {
    addSelectable(button);
}

void ButtonHolder::addSelectable(Selectable *selectable) {
    selectables.push_back(std::shared_ptr<Selectable>(selectable));
    setDefaultDestinations(selectable);

    if (current_selection == -1) {
        current_selection = 0;
        selectables[0]->select();
    }
}

void ButtonHolder::registerNewDestination(Selectable *selectable, sf::Keyboard::Key key, Selectable *destination) {
    selectable->setIfDefault(false);
    selectable->registerNewDestination(key, destination);
}

void ButtonHolder::removeAllDestinations(Selectable *selectable) {
    selectable->setIfDefault(false);
    selectable->removeAllDestinations();
}

void ButtonHolder::removeDestination(Selectable *selectable, sf::Keyboard::Key key) {
    selectable->setIfDefault(false);
    selectable->removeDestination(key);
}

void ButtonHolder::setDefaultDestinations(Selectable *selectable) {
    removeAllDestinations(selectable);
    int position = findSelectable(selectable);
    selectable->setIfDefault(true);

    Selectable *tmp = selectables[(position + 1) % selectables.size()].get();
    selectable->registerNewDestination(sf::Keyboard::S, tmp);
    if (tmp->isDefault())
        tmp->registerNewDestination(sf::Keyboard::W, selectable);

    tmp = selectables[((position == 0) ? selectables.size() - 1 : position - 1)].get();
    selectable->registerNewDestination(sf::Keyboard::W, tmp);
    if (tmp->isDefault())
        tmp->registerNewDestination(sf::Keyboard::S, selectable);
}

void ButtonHolder::interceptInput(Selectable *interceptor) {
    input_interceptor = interceptor;
}

void ButtonHolder::stopInputForwarding() {
    input_interceptor = nullptr;
}

void ButtonHolder::changeSelection(Selectable *selectable) {
    if (selectable == nullptr)
        return;

    selectables[current_selection]->deselect();
    current_selection = findSelectable(selectable);
    selectables[current_selection]->select();
}

void ButtonHolder::moveCurrentPosition(sf::Keyboard::Key key) {
    changeSelection(selectables[current_selection]->getNextSelectable(key));
}

int ButtonHolder::findSelectable(Selectable *selectable) {
    for (int i = 0; i < selectables.size(); i++)
        if (selectables[i].get() == selectable)
            return i;
    
    return -1;
}