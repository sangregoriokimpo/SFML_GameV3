

#ifndef SFML_GAMEV3_BULLETV2_H
#define SFML_GAMEV3_BULLETV2_H


#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include <iostream>



class BulletV2 {
private:
    sf::Sprite sprite;
    sf::Vector2f velocity;
    bool active;


public:
    /*BulletV2(sf::Texture& texture, sf::Vector2f position, sf::Vector2f direction, float speed) {
        sprite.setTexture(texture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2); // Set origin to center
        sprite.setPosition(position);
        sprite.setRotation(atan2(direction.y, direction.x) * 180 / M_PI); // Set rotation towards direction
        sprite.setScale(0.125f,0.125f);
        velocity = direction * speed;


    }*/

    BulletV2(const sf::Texture& texture, const sf::Vector2f& position, const sf::Vector2f& direction, float speed)
            : velocity(direction * speed) {
        sprite.setTexture(texture);
        sprite.setOrigin(sprite.getLocalBounds().width / 2, sprite.getLocalBounds().height / 2); // Set origin to center
        sprite.setPosition(position);
        sprite.setRotation(atan2(direction.y, direction.x) * 180 / M_PI); // Set rotation towards direction
        //sprite.setScale(0.125f,0.125f);
        velocity = direction * speed;
        active = true;

    }

    void update(float deltaTime) {
        // Scale the velocity vector by deltaTime
        sf::Vector2f deltaPosition = velocity * deltaTime;

        // Move the sprite by the scaled velocity
        sprite.move(deltaPosition);
    }


    void draw(sf::RenderWindow& window) {
        window.draw(sprite);
    }

    sf::Vector2f getPosition() const {
        return sprite.getPosition();
    }

    const sf::Sprite &getSprite() const {
        return sprite;
    }

    void checkCollision(std::vector<Enemy>& enemies) {
        sf::FloatRect bulletBounds = sprite.getGlobalBounds(); // Get the global bounds of the bullet sprite

        for (auto& enemy : enemies) {
            sf::FloatRect enemyBounds = enemy.getSprite().getGlobalBounds(); // Get the global bounds of the enemy sprite

            // Check if the bullet bounds intersect with the enemy bounds
            if (bulletBounds.intersects(enemyBounds)) {
                // If there's an intersection, handle the collision
                std::cout << enemy.getHealth() << std::endl;
                enemy.takeDamage(10);
                active = false; // Deactivate the bullet
                return; // Exit the loop early since the bullet can only collide with one enemy
            }
        }
    }


    bool isActive() const {
        return active;
    }

    void setActive(bool active) {
        BulletV2::active = active;
    }
};


#endif //SFML_GAMEV3_BULLETV2_H
