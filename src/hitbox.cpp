#include "../include/hitbox.h"
#include "../include/entity.h"

#include "../include/utility.h"

Hitbox::Hitbox(Entity *entity)
: entity(entity)
, rectangles() {}

// void Hitbox::addRectangle(sf::RectangleShape *rectangle) {
//     rectangles.push_back(std::unique_ptr<sf::RectangleShape>(rectangle));
// }

bool Hitbox::doesIntersect(Hitbox &hitbox) { return false; }
//     sf::Transform own_transform = entity->getTransform();
//     sf::Transform other_transform = hitbox.getEntity()->getTransform();

//     for(auto &rect1 : rectangles)
//         for(auto &rect2 : *hitbox.getRectangles())
//             if(doRectanglesIntersect(*rect1 * own_transform, *rect2 * other_transform))
//                 return true;
// }

std::vector<sf::RectangleShape> *Hitbox::getRectangles() {
    return &rectangles;
}

Entity *Hitbox::getEntity() {
    return entity;
}

void Hitbox::draw(sf::RenderWindow &window) {
    for (sf::RectangleShape rec : rectangles) {
        rec.setOutlineColor(sf::Color::Green);
        rec.setOutlineThickness(1);
        rec.setFillColor(sf::Color::Transparent);

        sf::CircleShape eee{3};
        centerOrigin(eee);
        eee.setPosition(rec.getPosition());
        eee.setFillColor(sf::Color::Yellow);
        window.draw(eee);

        window.draw(rec);
    }
}

// bool doRectanglesIntersect(sf::RectangleShape &rect1, sf::RectangleShape &rect2) {
//     return rect1.getGlobalBounds().intersects(rect2.getGlobalBounds());
// }