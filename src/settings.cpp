#include "../include/settings.h"

TeamOptionField(ButtonHolder& button_holder, sf::Vector2f size, sf::Vector2f position, sf::Color team_color, int nr_of_ships);

void input(sf::Event event);
void update(sf::Time dt);
void draw(sf::RenderWindow& window);

void activate();
private:
static const sf::Color background_color;
static const sf::Color outline_color;
static const sf::Color selection_color;



Settings::Settings(sf::RenderWindow& window, ScreenHolder& screen_holder, std::vector<int>& ship_counts)
: Screen(window, screen_holder)
, ship_counts(ship_counts) {}

bool Settings::input(sf::Event event) {}
bool Settings::update(sf::Time dt) {}
bool Settings::draw() {}