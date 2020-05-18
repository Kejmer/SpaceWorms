#include "../include/settings.h"
#include "../include/button.h"
#include "../include/utility.h"
#include "../include/screenHolder.h"

const sf::Color TeamOptionField::background_color = sf::Color(214, 177, 26);
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
    Selectable::setPosition(position);

    centerOrigin(background);
    background.setPosition(position);
    background.setFillColor(background_color);

    ships.setColor(sf::Color::Black);

    ships_nr.setBackground(sf::Color(119, 131, 153));
    ships_nr.setColor(sf::Color::Black);

    centerOrigin(team_indicator);
    team_indicator.setFillColor(team_color);
    team_indicator.setOutlineThickness(2);
    team_indicator.setOutlineColor(sf::Color::Black);
    team_indicator.setPosition({background.getGlobalBounds().left + team_indicator.getSize().x / 2 + 5, background.getPosition().y});
    initButtons();
    calculatePositions();
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

void TeamOptionField::setPosition(sf::Vector2f position) {
    Selectable::setPosition(position);

    background.setPosition(position);
    calculatePositions();
}

void TeamOptionField::calculatePositions() {
    float quarter = (background.getSize().x - team_indicator.getSize().x - 10) / 4;
    float offset = (team_indicator.getSize().x + 10);

    ships.setPosition(position - sf::Vector2f{quarter - offset, 0});
    ships_nr.setPosition(position + sf::Vector2f{quarter + offset, 0});
    team_indicator.setPosition({background.getGlobalBounds().left + team_indicator.getSize().x / 2 + 5, background.getPosition().y});
    
    getSelectable(0)->setPosition(background.getPosition() + sf::Vector2f{quarter / 2 + offset, 0});
    getSelectable(1)->setPosition(background.getPosition() + sf::Vector2f{quarter * 3 / 2 + offset, 0});
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
    registerNewDestination(decrement, sf::Keyboard::Right, increment);
    registerNewDestination(increment, sf::Keyboard::Left, decrement);
}


const int Settings::max_teams = 5;
const float Settings::space_between_buttons = 10;

Settings::Settings(sf::RenderWindow& window, ScreenHolder& screen_holder, std::vector<int>& ship_counts, const std::vector<sf::Color>& team_colors)
: Screen(window, screen_holder)
, ship_counts(ship_counts)
, team_colors(team_colors)
, teams()
, buttons()
, new_team()
, remove_team()
, title(nullptr, L"Ustawienia drużyn", {512, 134}, 60)
, existing_teams(0) {
    initTeams();

    remove_team = new Button(buttons, {512, 204}, {700, 50}, sf::Color(119, 131, 153), sf::Color::Blue);
    remove_team->setText(L"Usuń ostatnią drużynę");
    remove_team->assignAction([this](){
        if (existing_teams == 2)
            return;

        removeTeam();
    });
    if (existing_teams == 2)
        remove_team->setIfEnabled(false);
    buttons.addSelectable(remove_team);

    new_team = new Button(buttons, {512, 264}, {700, 50}, sf::Color(119, 131, 153), sf::Color::Blue);
    new_team->setText(L"Dodaj nową drużynę");
    new_team->assignAction([this](){
        if (existing_teams == max_teams)
            return;

        addTeam();
    });
    if (existing_teams == max_teams)
        new_team->setIfEnabled(false);
    buttons.addSelectable(new_team);

    Button *go_back = new Button(buttons, {512, 324}, {700, 50}, sf::Color(119, 131, 153), sf::Color::Blue);
    go_back->setText(L"Zapisz i wróć do menu");
    go_back->assignAction([this](){
        this->screen_holder.pop_back();
    });
    buttons.addSelectable(go_back);

    updatePositions();
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
    title.draw(window);
    buttons.draw(window);

    return false;
}

void Settings::initTeams() {
    bool stop_adding = false;

    for (int i = 0; i < 5; i++) {
        buttons.addSelectable(new TeamOptionField(buttons, {700, 50}, {0, 0}, team_colors[i], i, ship_counts));
        buttons.getSelectable(i)->setIfEnabled(false);
        if (ship_counts[i] == 0)
            stop_adding = true;

        if (!stop_adding) {
            buttons.getSelectable(existing_teams)->setIfEnabled(true);
            existing_teams++;
        }
    }
}

void Settings::addTeam() {
    ship_counts[existing_teams] = 1;
    buttons.getSelectable(existing_teams)->setIfEnabled(true);
    existing_teams++;

    if (existing_teams == max_teams) {
        new_team->setIfEnabled(false);
        buttons.changeSelection(remove_team);
    }
    
    if (existing_teams > 2)
        remove_team->setIfEnabled(true);

    updatePositions();
}

void Settings::removeTeam() {
    existing_teams--;
    ship_counts[existing_teams] = 0;
    buttons.getSelectable(existing_teams)->setIfEnabled(false);

    if (existing_teams < max_teams)
        new_team->setIfEnabled(true);

    if (existing_teams == 2) {
        remove_team->setIfEnabled(false);
        buttons.changeSelection(new_team);
    }

    updatePositions();
}

void Settings::updatePositions() {
    sf::Vector2f current_position{512, 204};

    for (int i = 0; i < buttons.size(); i++) {
        Selectable *button = buttons.getSelectable(i);
        if (!button->isEnabled())
            continue;

        button->setPosition(current_position);
        current_position.y += 60;
    }
}
