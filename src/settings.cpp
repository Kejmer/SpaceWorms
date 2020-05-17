#include "../include/settings.h"
#include "../include/button.h"
#include "../include/utility.h"

const sf::Color TeamOptionField::background_color = sf::Color::Yellow;
const sf::Color TeamOptionField::selection_color = sf::Color::Red;
const int TeamOptionField::max_ships = 3;

TeamOptionField::TeamOptionField(ButtonHolder& button_holder, sf::Vector2f size, sf::Vector2f position, sf::Color team_color, int team_nr, std::vector<int>& ship_counts)
: button_holder(button_holder)
, team_color(team_color)
, team_nr(team_nr)
, ship_counts(ship_counts)
, nr_of_ships(ship_counts[team_nr])
, background(size)
, team_indicator({size.y - 10, size.y - 10})
, ships_nr(nullptr, std::to_string(nr_of_ships))
, ships(nullptr, L"Liczba statków: ")
, buttons()
, has_focus(false) {
    float quarter = (background.getSize().x - team_indicator.getSize().x - 10) / 4;
    float offset = (team_indicator.getSize().x + 10);

    centerOrigin(background);
    background.setPosition(position);
    background.setFillColor(background_color);

    ships.setPosition(position - sf::Vector2f{quarter - offset, 0});
    ships.setBackground(sf::Color::Cyan);

    ships_nr.setPosition(position + sf::Vector2f{quarter + offset, 0});
    ships_nr.setBackground(sf::Color::Cyan);

    centerOrigin(team_indicator);
    team_indicator.setFillColor(team_color);
    team_indicator.setOutlineThickness(2);
    team_indicator.setOutlineColor(sf::Color::Black);
    team_indicator.setPosition({background.getGlobalBounds().left + team_indicator.getSize().x / 2 + 5, background.getPosition().y});
    initButtons();
}

void TeamOptionField::input(sf::Event event) {
    if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape) {
        has_focus = false;
        button_holder.stopInputForwarding();
    }
    else
        ButtonHolder::input(event);
}

void TeamOptionField::update(sf::Time dt) {
    nr_of_ships = ship_counts[team_nr];
    ships_nr.updateString(std::to_string(nr_of_ships));
}

void TeamOptionField::draw(sf::RenderWindow& window) {
    if (is_selected) {
        sf::RectangleShape tmp;
        tmp.setSize(background.getSize() + sf::Vector2f{5, 5});
        centerOrigin(tmp);
        tmp.setPosition(background.getPosition());
        tmp.setFillColor(selection_color);

        window.draw(tmp);

        sf::CircleShape pointer{20, 3};
        centerOrigin(pointer);
        pointer.setFillColor(selection_color);
        pointer.setPosition({background.getGlobalBounds().left - 10 - pointer.getRadius(), background.getPosition().y});
        pointer.setRotation(90);
        window.draw(pointer);
    }

    window.draw(background);
    window.draw(team_indicator);
    ships_nr.draw(window);
    ships.draw(window);

    if (!has_focus)
        selectables[current_selection]->deselect();
    else
        selectables[current_selection]->select();

    ButtonHolder::draw(window);
}

void TeamOptionField::activate() {
    ButtonHolder::activate();
    button_holder.interceptInput(this);
    has_focus = true;
}

void TeamOptionField::initButtons() {
    float quarter = (background.getSize().x - team_indicator.getSize().x - 10) / 4;
    float offset = (team_indicator.getSize().x + 10);
    Button *decrement = new Button{*this, background.getPosition() + sf::Vector2f{quarter / 2 + offset, 0}, team_indicator.getSize(), sf::Color(119, 131, 153), sf::Color::Blue};

    decrement->setText("-");
    decrement->assignAction([this](){
        if (ship_counts[team_nr] > 1)
            ship_counts[team_nr]--;
    });
    addSelectable(decrement);

    Button *increment = new Button{*this, background.getPosition() + sf::Vector2f{quarter * 3 / 2 + offset, 0}, team_indicator.getSize(), sf::Color(119, 131, 153), sf::Color::Blue};
    increment->setText("+");
    increment->assignAction([this](){
        if (ship_counts[team_nr] < max_ships)
            ship_counts[team_nr]++;
    });
    addSelectable(increment);

    registerNewDestination(decrement, sf::Keyboard::D, increment);
    registerNewDestination(increment, sf::Keyboard::A, decrement);
}

Settings::Settings(sf::RenderWindow& window, ScreenHolder& screen_holder, std::vector<int>& ship_counts)
: Screen(window, screen_holder)
, ship_counts(ship_counts)
, teams()
, buttons() {
    buttons.addSelectable(new TeamOptionField(buttons, {700, 50}, {512, 200}, sf::Color::Red, 0, ship_counts));
    buttons.addSelectable(new TeamOptionField(buttons, {700, 50}, {512, 500}, sf::Color::Blue, 1, ship_counts));
}

bool Settings::input(sf::Event event) {
    buttons.input(event);

    return false;
}

bool Settings::update(sf::Time dt) {
    buttons.update(dt);

    return false;
}

bool Settings::draw() {
    buttons.draw(window);

    return false;
}