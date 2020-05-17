#include "../include/screenManager.h"
#include "../include/world.h"
#include "../include/asteroid.h"

const sf::Time ScreenManager::frame_time = sf::seconds(1./60.);

ScreenManager::ScreenManager(sf::RenderWindow& window)
: window(window)
, screen_holder() {
    init();
}

void ScreenManager::run() {
    sf::Clock clock;
    sf::Time last_update = sf::Time::Zero;

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        last_update += elapsed;
        while (last_update > frame_time) {
            last_update -= frame_time;

            input();
            screen_holder.update(frame_time);
        }
        draw();
        screen_holder.applyChanges();

        if (screen_holder.isEmpty()) {
            window.close();
            return;
        }
    }
}

void ScreenManager::draw() {
    window.clear(sf::Color::Black);
    screen_holder.draw();
    window.display();
}

void ScreenManager::input() {
    sf::Event event;
    while (window.pollEvent(event)) {
        screen_holder.input(event);

        if (event.type == sf::Event::Closed)
            window.close();
    }
}

void ScreenManager::init() {
    World *world = new World(window, screen_holder);

    world->addHoleEntity(new BlackHole({500, 500}, 700, 30));
    world->addHoleEntity(new BlackHole({700, 300}, 500, 20));
    world->newTeam(sf::Color::Red);
    world->newTeam(sf::Color::Blue);
    world->newShip({100,100}, 1);
    world->newShip({100,300}, 1);
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

    world->run();
    screen_holder.push_back(world);
    screen_holder.applyChanges();
}