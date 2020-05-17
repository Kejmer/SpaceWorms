#include "../include/screenManager.h"
#include "../include/world.h"
#include "../include/asteroid.h"
#include "../include/mainMenu.h"

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
    MainMenu *menu = new MainMenu(window, screen_holder);
    screen_holder.push_back(menu);    
    screen_holder.applyChanges();
}