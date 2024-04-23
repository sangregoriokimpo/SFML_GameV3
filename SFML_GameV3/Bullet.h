

#ifndef SFML_GAMEV3_BULLET_H
#define SFML_GAMEV3_BULLET_H


#include <SFML/Graphics.hpp>

class Bullet {
private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
    sf::Sprite sprite;

public:
    Bullet(sf::Vector2f position, sf::Vector2f direction, float speed) {
        shape.setRadius(5);
        shape.setFillColor(sf::Color::Yellow);
        shape.setPosition(position);
        velocity = direction * speed;
    }

    void update() {
        shape.move(velocity);
    }

    void draw(sf::RenderWindow& window) {
        window.draw(shape);
    }

    sf::Vector2f getPosition() const {
        return shape.getPosition();
    }
};



#endif //SFML_GAMEV3_BULLET_H
