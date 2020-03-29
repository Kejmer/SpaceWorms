#include "../include/world.h"
#include "../include/circle.h"  // Just for testing
#include "../include/bullet.h"
#include "../include/spaceship.h"

#include <SFML/Graphics.hpp>
#include <memory>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");
    World world(window);
    sf::Vector2f v(100, 100);

    world.addEntity(new Circle({100, 100}, 100, sf::Color::Green));
    world.addEntity(new Circle({300, 600}, 150, sf::Color::Blue));
    world.addEntity(new SimpleBullet({400,400}, {40,10}));
    world.addEntity(new Spaceship({500, 500}));

    world.run();
    return 0;
}