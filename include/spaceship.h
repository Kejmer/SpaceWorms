#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "entity.h"
#include "bar.h"
#include "textBox.h"

#include <SFML/Graphics.hpp>
#include <map>

class Spaceship : public Entity {
public:
    enum Statistics {
        MaxHealth,
        Healthpoints,
        ShotsPerSecond,
        MoveSpeed,
        AmmoCount,
        BulletSpeed
    };

    Spaceship(sf::Vector2f position, std::string file="assets/spaceship_grey.png");
    void input(sf::Event event);
    void update(sf::Time dt);
    void draw(sf::RenderWindow& window);

    void shoot();
    void move(sf::Vector2f vector);

    void updateStatistics(Statistics stat, float new_value);
    float getStatistics(Statistics stat);
    int getID();

    void setTeam(int team_id);
private:
    void realtimeInput();
    sf::Vector2f getDirection();
    void createHitbox();
    void initStatistics();

    static int counter;
    int id;
    int team_id;

    std::map<Statistics, float> statistics_holder;
    sf::CircleShape ship;
    int rotation;
    float move_dir;
    sf::Time last_shot;
    sf::Texture texture;
    std::string file;


    Bar *healthbar;
    TextBox *ammo_text;
};

#endif