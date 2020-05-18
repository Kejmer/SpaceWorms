#ifndef WORLD_H
#define WORLD_H

#include "entity.h"
#include "hole.h"
#include "team.h"
#include "delayedContainer.h"
#include "powerUp.h"
#include "screen.h"
#include "defines.h"
#include "bulletFactory.h"

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>

class World : public Screen {
public:
    World(sf::RenderWindow& window, ScreenHolder& screen_holder);
    bool input(sf::Event event);
    bool update(sf::Time dt);
    bool draw();
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

    void shipDestroyed(int team_id, int ship_id);

    void spawnBullet(sf::Vector2f position, sf::Vector2f velocity);
    void spawnBullet(sf::Vector2f position, sf::Vector2f velocity, int type);

    int currentWeapon();

    void setCurrentWeapon(int pick);
private:
    void checkCollisions();
    /// Ustawienie następnej drużyny
    int nextTeam();
    /// Przekaż kontrolę następnemu statkowi
    void controlNext();
    /// Sprawdź input użytkownika dotyczący kontroli statków
    void userTeamControl(sf::Event event);

    void timeMultiplierChanges();

    /// Nałóż pauzę jeśli wciśnięto P
    void pauseMenu();

    DelayedContainer<GHole> holeEntities;

    bool requesterId;
    bool is_time_flowing;
    float gravity_multiplier = 900;
    float max_time_mult = 2;
    float time_multiplier = 1;

    static const sf::Time turn_time;
    sf::Time time_left;

    std::vector<std::shared_ptr<Team>> teams;
    int teams_remaining;
    int current_team;
    int current_ship;

    std::unique_ptr<Bar> game_speed_bar;
    std::unique_ptr<TextBox> game_speed_text;

    sf::Texture background_texture;

    std::vector<std::shared_ptr<AbsBulletFactory>> weapons;
    int current_weapon;
    void resetWeapon();
    void openInventory();
};

#endif