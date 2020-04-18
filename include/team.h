#ifndef TEAM_H
#define TEAM_H

#include "spaceship.h"

#include <vector>

class World;

class Team {
public:
  Team(sf::Color color);
  /// Zwraca id kolejnego statku w "kolejce"
  int nextShip();
  /// Ustawienie świata w który drużyna się znajduje
  void setWorld(World *world);
  /// Stworzenie statku należącego do tej drużyny na danej pozycji
  std::shared_ptr<Spaceship> addShip(sf::Vector2f position);
  /// Zwróć id drużyny
  int getID();
private:
  /// Id indentyfikujący drużynę
  int id;
  /// Licznik wszystkich istniejących drużyn
  static int counter;
  /// Ostatni statek przekazany do świata
  int last_ship;
  /// Idki statków należących do tej drużyny
  std::vector<int> team_ships;
  /// Kolor identyfikujący drużynę
  sf::Color team_color;
  /// Wskaźnik na świat
  World *world;
  /// Nazwa pliku do ładowania obrazka
  std::string ship_file;
};


#endif /* TEAM_H */
