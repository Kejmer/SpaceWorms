#include "../include/spaceship.h"
#include "../include/utility.h"
#include "../include/world.h"
#include "../include/bullet.h"
#include "../include/complexHitbox.h"

int Spaceship::counter = 1;

Spaceship::Spaceship(sf::Vector2f position, std::string file)
: Entity(position, Entity::Spaceship)
, statistics_holder()
, ship(30, 3)
, rotation(0)
, move_dir(0)
, last_shot(sf::Time::Zero)
, healthbar()
, ammo_text() {
    centerOrigin(ship);
    ship.setPosition(position);

    texture.loadFromFile(file); // Może rzucić failem, jeśli nie załaduje obrazka, wtedy ładuje biały trójkąt. 
    ship.setTexture(&texture, true);
    id = counter++;

    initStatistics();

    healthbar = new Bar{this, sf::Color::Green, sf::Color::Red, {50, 5}, {0, 40}, getStatistics(MaxHealth), getStatistics(Healthpoints)};
    addAttachable(healthbar);

    ammo_text = new TextBox{this, "Ammo: " + std::to_string((int)getStatistics(AmmoCount)), {0, 57}, 14};
    addAttachable(ammo_text);

    createHitbox();
}

void Spaceship::input(sf::Event event) {}

void Spaceship::update(sf::Time dt) {
    if (id == world->getMoveRequest())
        world->clearRequest();

    last_shot += dt;
    healthbar->setValue(getStatistics(Healthpoints));

    if (id == world->getController()) {
        realtimeInput();

        sf::Vector2f direction = getDirection();
        move(direction * move_dir * getStatistics(MoveSpeed) * dt.asSeconds());
        ship.rotate(dt.asSeconds() * rotation * getStatistics(MoveSpeed));
        rotation = 0;
        move_dir = 0;

        hitbox->update();
    }
}

void Spaceship::draw(sf::RenderWindow& window) {
    window.draw(ship);
    // hitbox->draw(window);
    for (auto att : attachables_to_draw)
        att->draw(window);
}

void Spaceship::shoot() {
    if (getStatistics(AmmoCount) <= 0)
        return;

    sf::Vector2f direction = getDirection();
    world->addEntity(new SimpleBullet{position + direction * 35.f, direction * getStatistics(BulletSpeed)});
    updateStatistics(AmmoCount, getStatistics(AmmoCount) - 1);
    ammo_text->updateString("Ammo: " + std::to_string((int)getStatistics(AmmoCount)));
    last_shot = sf::Time::Zero;

    world->clearRequest();
    world->nextTurn();
}

void Spaceship::move(sf::Vector2f vector) {
    Entity::move(vector);
    ship.move(vector);
}

void Spaceship::updateStatistics(Spaceship::Statistics stat, float new_value) {
    statistics_holder[stat] = new_value;
}

float Spaceship::getStatistics(Spaceship::Statistics stat) {
    return statistics_holder[stat];
}

void Spaceship::realtimeInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        world->moveRequest(id);
        move_dir += 1;
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        world->moveRequest(id);
        move_dir -= 1;
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
        last_shot.asSeconds() >= 1. / getStatistics(ShotsPerSecond))
        shoot();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        rotation += 1;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        rotation -= 1;
}

sf::Vector2f Spaceship::getDirection() {
    float rotation = toRadian(ship.getRotation());
    return {sinf(rotation), -cosf(rotation)};
}

void Spaceship::createHitbox() {
    hitbox = std::unique_ptr<ComplexHitbox>(new ComplexHitbox{this, &ship});
    sf::FloatRect bounds = ship.getLocalBounds();
    sf::RectangleShape rect{{30, 30}};
    rect.setPosition(0, -ship.getOrigin().y);
    rect.rotate(45);
    hitbox->addRectangle(rect);

    rect.setSize({20, 20});
    centerOrigin(rect);
    rect.setPosition({-ship.getOrigin().x / 2, (bounds.height - ship.getOrigin().y) / 2});
    rect.rotate(-90);
    hitbox->addRectangle(rect);

    rect.move({-2 * rect.getPosition().x, 0});
    hitbox->addRectangle(rect);

    rect.move({-rect.getPosition().x, 0});
    rect.rotate(45);
    hitbox->addRectangle(rect);

    hitbox->update();
}

void Spaceship::initStatistics() {
    statistics_holder[MaxHealth] = 100;
    statistics_holder[Healthpoints] = 100;
    statistics_holder[ShotsPerSecond] = 3;
    statistics_holder[MoveSpeed] = 90;
    statistics_holder[AmmoCount] = 100;
    statistics_holder[BulletSpeed] = 100;
}

int Spaceship::getID() {
    return id;
}

void Spaceship::setTeam(int team_id) {
    this->team_id = team_id;
}