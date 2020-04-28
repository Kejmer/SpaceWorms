#include "../include/world.h"
#include "../include/circle.h"  // Just for testing
#include "../include/bullet.h"
#include "../include/hole.h"
#include "../include/spaceship.h"
#include "../include/team.h"
#include "../include/asteroid.h"

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
    world.addHoleEntity(new Asteroid({300,400}, 700, 30));

    // pas asteroid przy pierwszym statku
    world.addHoleEntity(new Asteroid({220,150}, 700, 15));
    world.addHoleEntity(new Asteroid({280,160}, 700, 10));
    world.addHoleEntity(new Asteroid({320,140}, 700, 10));
    world.addHoleEntity(new Asteroid({360,110}, 700, 20));
    world.addHoleEntity(new Asteroid({380,170}, 700, 15));
    world.addHoleEntity(new Asteroid({310,180}, 700, 15));
    // asteroidy za drugim statkiem
    world.addHoleEntity(new Asteroid({800,550}, 700, 15));
    world.addHoleEntity(new Asteroid({850,600}, 700, 10));
    world.addHoleEntity(new Asteroid({750,630}, 700, 20));

    // White Hole
    world.addHoleEntity(new WhiteHole({200,600}, 700, 30));


    world.run();
    return 0;
}