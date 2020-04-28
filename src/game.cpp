#include "../include/world.h"
#include "../include/circle.h"  // Just for testing
#include "../include/bullet.h"
#include "../include/hole.h"
#include "../include/spaceship.h"
#include "../include/team.h"

#include <SFML/Graphics.hpp>
#include <memory>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");
    World world(window);
    sf::Vector2f v(100, 100);

    world.addHoleEntity(new BlackHole({500, 500}, 700, 30));
    world.addHoleEntity(new BlackHole({700, 300}, 500, 20));
    world.newTeam(sf::Color::Red);
    world.newTeam(sf::Color::Blue);
    world.newShip({100,100}, 1);
    world.newShip({700,500}, 2);
    world.newPowerUp({200, 200}, PowerUp::Health);
    world.newPowerUp({600, 600}, PowerUp::Ammo);
    world.newPowerUp({400, 400}, PowerUp::Time);

    world.run();
    return 0;
}