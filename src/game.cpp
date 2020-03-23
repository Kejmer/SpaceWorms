#include "../include/world.h"
#include "../include/circle.h"  // Just for testing

#include <SFML/Graphics.hpp>
#include <memory>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");
    World world(window);
    sf::Vector2f v(100, 100);

    world.addEntity(new Circle({100, 100}, 100, sf::Color::Green));
    world.addEntity(new Circle({300, 600}, 150, sf::Color::Blue));
    world.run();
    return 0;
}