#ifndef WORLD_H
#define WORLD_H

#include "entity.h"
#include "hole.h"
#include "team.h"
#include "delayedContainer.h"
#include "powerUp.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class World {
public:
    World(sf::RenderWindow& window);
    void input();
    void update(sf::Time dt);
    void draw();
    void run();

    void addHoleEntity(GHole *hole);
    void removeHoleEntity(GHole *hole);

    std::shared_ptr<Entity> addEntity(Entity* entity);
    void addEntity(std::shared_ptr<Entity> entity);
    void removeEntity(Entity* entity);
    sf::Vector2f calcGravAccel(sf::Vector2f pos);

    bool isTimeFlowing();
    /// Statek o id spaceshipID próbuje wykonać ruch mimo zamrożonego czasu
    void moveRequest(int spaceshipID);
    /// Który statek poruszył się mimo zamrożonego czasu
    int getMoveRequest();
    /// Wyczyść informacje o statku
    void clearRequest();
    /// Dodaje statek do drużyny o id teamID
    void newShip(sf::Vector2f postion, int teamID);
    /// Dodaje nowy power up danego typu
    void newPowerUp(sf::Vector2f position, PowerUp::PowerUpType type);
    /// Dodanie do świata nowej drużyny reprezentowanej kolorem color
    int newTeam(sf::Color color);
    /// Który statek aktualnie jest kontrolowany
    int getController();
    /// Zablokuj możliwość kontroli statkiem aż upłynie czas do następnej tury
    void nextTurn();
    /// Przedłuż obecnie trwającą turę
    void extendTurn(sf::Time t);
private:
    void checkCollisions();
    /// Ustawienie następnej drużyny
    int nextTeam();
    /// Przekaż kontrolę następnemu statkowi
    void controlNext();

    void timeMultiplierChanges();

    sf::RenderWindow& window;
    DelayedContainer<GHole> holeEntities;
    DelayedContainer<Entity> entities;

    static const sf::Time frame_time;

    bool requesterId;
    bool is_time_flowing;
    float gravity_multiplier = 900;
    float max_time_mult = 2;
    float time_multiplier = 1;

    static const sf::Time turn_time;
    sf::Time time_left;

    std::vector<std::shared_ptr<Team>> teams;
    int current_team;
    int current_ship;

    Bar *game_speed_bar;
    TextBox *game_speed_text;
};

#endif