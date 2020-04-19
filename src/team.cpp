#include "../include/team.h"

int Team::counter = 1;

Team::Team(sf::Color color)
: last_ship(0)
, team_color(color) {
  id = counter++;
}

int Team::nextShip() {
  if (team_ships.size() == 0)
    return 0;
  last_ship++;
  last_ship %= team_ships.size();
  return team_ships[last_ship];
}

std::shared_ptr<Spaceship> Team::addShip(sf::Vector2f position) {
  auto ptr = std::make_shared<Spaceship>(position, team_color);
  ptr->setTeam(id);
  team_ships.push_back(ptr->getID());
  return ptr;
}

void Team::setWorld(World *world) {
    this->world = world;
}

int Team::getID() {
  return id;
}