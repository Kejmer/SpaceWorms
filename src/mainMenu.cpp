#include "../include/mainMenu.h"
#include "../include/button.h"
#include "../include/screenHolder.h"
#include "../include/world.h"
#include "../include/asteroid.h"
#include "../include/settings.h"

const std::vector<sf::Color> MainMenu::team_colors = {sf::Color::Red, sf::Color::Blue, sf::Color::Green, sf::Color::Yellow, sf::Color(119, 131, 153)};

MainMenu::MainMenu(sf::RenderWindow& window, ScreenHolder& screen_holder)
: Screen(window, screen_holder)
, button_holder()
, attachables()
, ship_counts() {

    ship_counts = {1, 1, 0, 0, 0};
    
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
        // world->newTeam(sf::Color::Red);
        // world->newTeam(sf::Color::Blue);
        // world->newShip({100,100}, 1);
        // world->newShip({700,500}, 2);
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
        initTeams(world);

        world->run();
        screen_holder.push_back(world);
    });
    button_holder.addButton(start);

    Button *settings = new Button(button_holder, {512, 434}, {400, 100}, sf::Color(119, 131, 153), sf::Color::Blue);
    settings->setText(L"Ustawienia");
    settings->assignAction([this](){
        Settings *settings_screen = new Settings{window, screen_holder, ship_counts, team_colors};
        screen_holder.push_back(settings_screen);
    });
    button_holder.addButton(settings);

    Button *quit_game = new Button(button_holder, {512, 584}, {400, 100}, sf::Color(119, 131, 153), sf::Color::Blue);
    quit_game->setText(L"Wyjście");
    quit_game->assignAction([this](){
        screen_holder.clear();
    });
    button_holder.addButton(quit_game);
}

void MainMenu::initAttachables() {
    attachables.push_back(std::shared_ptr<Attachable>(new TextBox(nullptr, L"Space Worms", {512, 134}, 60)));
}

void MainMenu::initTeams(World *world) {
    std::vector<std::pair<int, int>> rectangles;
    float rect_width = window.getSize().x / 10;
    float rect_height = window.getSize().y / 10;

    for (int i = 0; i < 10; i++)
        for (int j = 0; j < 10; j++)
            rectangles.push_back(std::make_pair(i, j));

    std::random_shuffle(rectangles.begin(), rectangles.end());
    int count = 0;

    for (int i = 0; i < 5; i++) {
        if (ship_counts[i] == 0)
            break;

        world->newTeam(team_colors[i]);
        for (int j = 0; j < ship_counts[i]; j++) {
            auto rect = rectangles[count];
            count++;

            float pos_x = rect.first * rect_width + rect_width / 2;
            float pos_y = rect.second * rect_height + rect_height / 2;
            world->newShip({pos_x, pos_y}, i + 1);
        }
    }
}