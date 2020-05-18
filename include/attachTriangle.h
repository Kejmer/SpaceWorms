#ifndef ATTACH_TRIANGLE_H
#define ATTACH_TRIANGLE_H

#include <SFML/Graphics.hpp>

#include "attachable.h"

class AttachTriangle : public Attachable {
public:
    AttachTriangle(Entity *entity, sf::Color color, float size, sf::Vector2f position, bool visibility, float rotation = 180);
    
    void draw(sf::RenderWindow &window);

    bool getVisibility();
    void setVisibility(bool vis);
private:
    sf::Color color;
    sf::CircleShape shape;
    bool visible;
};

#endif