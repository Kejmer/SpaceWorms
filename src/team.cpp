#include "../include/team.h"

int Team::counter = 1;

Team::Team(sf::Color color)
: last_ship(0)
, team_color(color) {
  id = counter++;
  if (color == sf::Color::Red) {
    ship_file = "assets/spaceship_red1.png";
  }
  else if (color == sf::Color::Blue) {
    ship_file = "assets/spaceship_blue1.png";
  }
  else if (color == sf::Color::Yellow) {
    ship_file = "assets/spaceship_yellow1.png";
  }
  else if (color == sf::Color::Green) {
    ship_file = "assets/spaceship_green1.png";
  }
  else {
    ship_file = "assets/spaceship_grey1.png";
  }
}

int Team::nextShip() {
  if (team_ships.size() == 0)
    return 0;
  last_ship++;
  last_ship %= team_ships.size();
  return team_ships[last_ship];
}

std::shared_ptr<Spaceship> Team::addShip(sf::Vector2f position) {
  auto ptr = std::make_shared<Spaceship>(position, ship_file);
  team_ships.push_back(ptr->getID());
  return ptr;
}

void Team::setWorld(World *world) {
    this->world = world;
}

int Team::getID() {
  return id;
}