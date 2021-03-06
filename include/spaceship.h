#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "entity.h"
#include "bar.h"
#include "textBox.h"
#include "attachTriangle.h"

#include <SFML/Graphics.hpp>
#include <map>

class Team;

class Spaceship : public Entity {
public:
    enum Statistics {
        MaxHealth,
        Healthpoints,
        ShotsPerSecond,
        MoveSpeed,
        AmmoCount,
        BulletSpeed,
        ShotChargeTime
    };

    Spaceship(sf::Vector2f position, Team& team, std::string file="assets/spaceship_grey.png");
    void input(sf::Event event);
    void update(sf::Time dt);
    void draw(sf::RenderWindow& window);

    void shoot();
    void move(sf::Vector2f vector);

    void updateStatistics(Statistics stat, float new_value);
    float getStatistics(Statistics stat);
    int getID();

    void setTeam(int team_id);
    void setTeam(Team& team);
    int getTeam();

    std::shared_ptr<AttachTriangle> getCurrPlIndicator();
  
    static void resetCounter();
private:
    void realtimeInput();
    sf::Vector2f getDirection();
    void createHitbox();
    void initStatistics();

    static int counter;
    int id;
    int team_id;
    Team& team;

    std::map<Statistics, float> statistics_holder;
    sf::CircleShape ship;
    int rotation;
    float move_dir;
    sf::Time last_shot;
    sf::Texture texture;
    std::string file;
    int current_texture;

    bool isCharging;
    sf::Time charge_time;

    std::shared_ptr<Bar> healthbar;
    std::shared_ptr<Bar> shot_charge;
    std::shared_ptr<TextBox> ammo_text;
    std::shared_ptr<AttachTriangle> curr_player_indicator;
    std::shared_ptr<Bar> fuel_bar;
};

#endif