#include "../include/mainMenu.h"
#include "../include/button.h"
#include "../include/screenHolder.h"
#include "../include/world.h"
#include "../include/asteroid.h"

MainMenu::MainMenu(sf::RenderWindow& window, ScreenHolder& screen_holder)
: Screen(window, screen_holder)
, button_holder()
, attachables() {
    initButtons();
    initAttachables();
}

bool MainMenu::input(sf::Event event) {
    button_holder.input(event);
    return false;
}

bool MainMenu::update(sf::Time dt) {
    button_holder.update(dt);
    return false;
}

bool MainMenu::draw() {
    button_holder.draw(window);

    for (auto& att : attachables)
        att->draw(window);
    return false;
}

void MainMenu::initButtons() {
    Button *start = new Button(button_holder, {512, 284}, {400, 100}, sf::Color(119, 131, 153), sf::Color::Blue);
    start->setText(L"Rozpocznij grę");
    start->assignAction([this](){
        screen_holder.clear();
        
        World *world = new World(window, screen_holder);
        world->addHoleEntity(new BlackHole({500, 500}, 700, 30));
        world->addHoleEntity(new BlackHole({700, 300}, 500, 20));
        world->newTeam(sf::Color::Red);
        world->newTeam(sf::Color::Blue);
        world->newShip({100,100}, 1);
        world->newShip({700,500}, 2);
        world->newPowerUp({200, 200}, PowerUp::Health);
        world->newPowerUp({600, 600}, PowerUp::Ammo);
        world->newPowerUp({400, 400}, PowerUp::Time);
        world->addHoleEntity(new Asteroid({300,400}, 700, 30));

        // pas asteroid przy pierwszym statku
        world->addHoleEntity(new Asteroid({220,150}, 700, 15));
        world->addHoleEntity(new Asteroid({280,160}, 700, 10));
        world->addHoleEntity(new Asteroid({320,140}, 700, 10));
        world->addHoleEntity(new Asteroid({360,110}, 700, 20));
        world->addHoleEntity(new Asteroid({380,170}, 700, 15));
        world->addHoleEntity(new Asteroid({310,180}, 700, 15));
        // asteroidy za drugim statkiem
        world->addHoleEntity(new Asteroid({800,550}, 700, 15));
        world->addHoleEntity(new Asteroid({850,600}, 700, 10));
        world->addHoleEntity(new Asteroid({750,630}, 700, 20));

        // White Hole
        world->addHoleEntity(new WhiteHole({200,600}, 800, 30));


        world->run();
        screen_holder.push_back(world);
    });
    button_holder.addButton(start);

    Button *settings = new Button(button_holder, {512, 434}, {400, 100}, sf::Color(119, 131, 153), sf::Color::Blue);
    settings->setText(L"Ustawienia");
    button_holder.addButton(settings);

    Button *exit = new Button(button_holder, {512, 584}, {400, 100}, sf::Color(119, 131, 153), sf::Color::Blue);
    exit->setText(L"Wyjście");
    exit->assignAction([this](){
        screen_holder.clear();
    });
    button_holder.addButton(exit);
}

void MainMenu::initAttachables() {
    attachables.push_back(std::shared_ptr<Attachable>(new TextBox(nullptr, L"Space Worms", {512, 134}, 60)));
}