#include "../include/hitbox.h"
#include "../include/entity.h"
#include "../include/utility.h"

using Edge = std::pair<sf::Vector2<double>, sf::Vector2<double>>;

inline void transformPoint(sf::Vector2<double> &target, sf::Vector2f point, sf::Transform &transform) {
    auto result = transform.transformPoint(point);
    target.x = (double)result.x;
    target.y = (double)result.y;
}

std::vector<Edge> getEdges(sf::RectangleShape &rect) {
    sf::Transform transform = rect.getTransform();
    sf::Vector2<double> lt, rt, rb, lb;
    sf::FloatRect localRect = rect.getLocalBounds();
    std::vector<Edge> result;

    transformPoint(lt, {localRect.left, localRect.top}, transform);
    transformPoint(rt, {localRect.left + localRect.width, localRect.top}, transform);
    transformPoint(rb, {localRect.left + localRect.width, localRect.top + localRect.height}, transform);
    transformPoint(lb, {localRect.left, localRect.top + localRect.height}, transform);

    result.push_back(std::make_pair(lt, rt));
    result.push_back(std::make_pair(rt, rb));
    result.push_back(std::make_pair(rb, lb));
    result.push_back(std::make_pair(lb, lt));

    return result;
}

inline double det(sf::Vector2<double> a, sf::Vector2<double> b, sf::Vector2<double> c) {
    a.y *= -1;
    b.y *= -1;
    c.y *= -1;
    return a.x * b.y + a.y * c.x + b.x * c.y - a.x * c.y - a.y * b.x - b.y * c.x;
}

bool doSegmentsIntersect(Edge &edge1, Edge &edge2) {
    return (det(edge1.first, edge1.second, edge2.first) * det(edge1.first, edge1.second, edge2.second) < 0 &&
            det(edge2.first, edge2.second, edge1.first) * det(edge2.first, edge2.second, edge1.second) < 0);
}

bool isInside(std::vector<Edge> &edgesOutside, std::vector<Edge> &edgesInside) {
    for (auto edgeOutside : edgesOutside)
        for (auto edgeInside : edgesInside)
            if (det(edgeOutside.first, edgeOutside.second, edgeInside.first) > 0)
                return false;

    return true;
}

Hitbox::Hitbox(Entity *entity)
: entity(entity)
, rectangles() {}

void Hitbox::addRectangle(sf::RectangleShape rectangle) {}

bool Hitbox::doesIntersect(Hitbox &hitbox) {
    auto otherRectangles = hitbox.getRectangles();

    for (auto &myRect : rectangles) {
        auto myEdges = getEdges(myRect);
        
        for (auto &otherRect : *otherRectangles) {
            auto otherEdges = getEdges(otherRect);
            for (auto &myEdge : myEdges)
                for (auto &otherEdge : otherEdges)
                    if (doSegmentsIntersect(myEdge, otherEdge))
                        return true;

            if (isInside(myEdges, otherEdges) || isInside(otherEdges, myEdges))
                return true;
        }
    }

    return false;
}

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

        sf::CircleShape origin{3};
        centerOrigin(origin);
        origin.setPosition(rec.getPosition());
        origin.setFillColor(sf::Color::Yellow);
        window.draw(origin);

        window.draw(rec);
    }
}
