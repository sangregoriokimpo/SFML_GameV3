

#ifndef SFML_GAMEV3_SHOOTINGSYSTEMV2_H
#define SFML_GAMEV3_SHOOTINGSYSTEMV2_H


#include "Entity.h"
#include "Enemy.h"
#include "Bullet.h"
#include "BulletV2.h"
#include <vector>
#include <SFML/Audio/Sound.hpp>
#include <iostream>

class ShootingSystemV2 {
private:
    sf::Sprite& playerSprite; // Reference to the player's sprite
    std::vector<BulletV2> bullets; // Vector to store bullets
    float bulletSpeed; // Speed of bullets
    sf::Texture bulletTexture;
    sf::Clock fireRateClock; // Clock to track fire rate cooldown
    sf::Time fireRateInterval; // Interval between shots

public:
    ShootingSystemV2(sf::Sprite& playerSprite, float bulletSpeed, float fireRate)
            : playerSprite(playerSprite), bulletSpeed(bulletSpeed), fireRateInterval(sf::seconds(60.0f / fireRate)) {
        if(!bulletTexture.loadFromFile("../bullets/frame_0.png")){
            return;
        }
    }

    // Shoot a bullet towards the direction of the mouse if the fire rate allows
    void shootBullet(sf::RenderWindow& window) {
        if (fireRateClock.getElapsedTime() >= fireRateInterval) {
            // Get the current view of the window
            sf::View view = window.getView();

            // Get the world mouse position (window coordinates to world coordinates)
            sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
            sf::Vector2f worldMousePosition = window.mapPixelToCoords(pixelPos);

            // Calculate the direction vector from the player to the mouse
            sf::Vector2f direction = worldMousePosition - playerSprite.getPosition();

            // Normalize the direction vector
            float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
            direction /= length;

            // Create and add a bullet to the vector of bullets
            bullets.emplace_back(bulletTexture,playerSprite.getPosition(),direction,bulletSpeed);

            // Restart the fire rate cooldown clock
            fireRateClock.restart();
        }
    }


    // Update all bullets
    void updateBullets(float deltaTime) {
        for (auto& bullet : bullets) {
            bullet.update(deltaTime);
        }
    }

    // Draw all bullets
    void drawBullets(sf::RenderWindow& window) {
        for (auto& bullet : bullets) {
            bullet.draw(window);
        }
    }

    // Check for collisions between bullets and enemies
    void checkBulletEnemyCollision(std::vector<Enemy>& enemies) {
        for (auto bulletIt = bullets.begin(); bulletIt != bullets.end(); ) {
            bulletIt->checkCollision(enemies);

            // Check if the bullet is inactive, and if so, remove it from the vector
            if (!bulletIt->isActive()) {
                bulletIt = bullets.erase(bulletIt);
            } else {
                ++bulletIt;
            }
        }
    }

    // Clear all bullets
    void clearBullets() {
        bullets.clear();
    }

    // Draw the aiming line from player to mouse cursor
    void drawLineToMouse(sf::RenderWindow& window) {
        // Get the world mouse position (window coordinates to world coordinates)
        sf::Vector2f worldMousePosition = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        // Calculate the direction vector from the player to the mouse
        sf::Vector2f direction = worldMousePosition - playerSprite.getPosition();

        // Calculate the length of the direction vector
        float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);

        // Normalize the direction vector
        direction /= length;

        // Create a vertex array for the line
        sf::VertexArray line(sf::LinesStrip);

        // Add the player's position as the first vertex
        line.append(sf::Vertex(playerSprite.getPosition(), sf::Color::Red));

        // Define the gradient colors (start and end colors)
        sf::Color startColor(255, 0, 0); // Red
        sf::Color endColor(255, 255, 255); // White

        // Calculate the color step for each vertex
        float colorStep = 1.0f / length;
        sf::Color currentColor = startColor;

        // Interpolate colors along the line and add vertices to the vertex array
        for (float i = 0; i < length; ++i) {
            sf::Color interpolatedColor = sf::Color(
                    static_cast<sf::Uint8>((1.0f - i * colorStep) * startColor.r + i * colorStep * endColor.r),
                    static_cast<sf::Uint8>((1.0f - i * colorStep) * startColor.g + i * colorStep * endColor.g),
                    static_cast<sf::Uint8>((1.0f - i * colorStep) * startColor.b + i * colorStep * endColor.b)
            );
            line.append(sf::Vertex(playerSprite.getPosition() + i * direction, interpolatedColor));
        }

        // Add the mouse position as the last vertex
        line.append(sf::Vertex(worldMousePosition, sf::Color::White));

        // Draw the line
        window.draw(line);
    }
};




#endif //SFML_GAMEV3_SHOOTINGSYSTEMV2_H
