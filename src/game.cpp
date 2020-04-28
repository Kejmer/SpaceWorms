#include "../include/world.h"
#include "../include/circle.h"  // Just for testing
#include "../include/bullet.h"
#include "../include/hole.h"
#include "../include/spaceship.h"
#include "../include/team.h"
#include "../include/asteroid.h"
#include "../include/screenManager.h"

#include <SFML/Graphics.hpp>
#include <memory>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");
    sf::Vector2f v(100, 100);
    ScreenManager manager(window);

    manager.run();
 
    return 0;
}