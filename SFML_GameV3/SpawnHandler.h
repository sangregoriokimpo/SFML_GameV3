

#ifndef SFML_GAMEV3_SPAWNHANDLER_H
#define SFML_GAMEV3_SPAWNHANDLER_H

#include "Enemy.h"
#include <vector>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>


class SpawnHandler {
private:
    std::vector<Enemy>& enemies; // Reference to the vector containing enemy objects
    sf::Texture enemyTexture; // Texture for creating new enemies
    Player& player; // Reference to the player
    sf::Time spawnInterval; // Interval between enemy spawns
    sf::Clock spawnClock; // Clock to track spawn time

public:
    SpawnHandler(std::vector<Enemy>& enemies, sf::Texture enemyTexture,Player& player, const sf::Time& spawnInterval)
            : enemies(enemies), enemyTexture(enemyTexture), player(player), spawnInterval(spawnInterval) {}

    void update(sf::RenderWindow& window,float deltaTime) {
        // Check if it's time to spawn a new enemy
        if (spawnClock.getElapsedTime() >= spawnInterval) {
            // Spawn a new enemy
            spawnEnemy(window);
            // Restart the spawn clock
            spawnClock.restart();
        }
        for(auto& enemy: enemies){
            enemy.update(window,deltaTime);
        }
    }

    void spawnEnemy(sf::RenderWindow& window) {
        // Get the size of the window
        sf::Vector2u windowSize = window.getSize();

        // Randomly select a direction (0: -x, 1: -y, 2: x, 3: y)
        int direction = rand() % 4;

        // Randomly generate coordinates outside the view of the camera for each direction
        float x, y;
        switch (direction) {
            case 0: // -x direction
                x = -static_cast<float>(rand() % 200 + 100);
                y = static_cast<float>(rand() % windowSize.y);
                break;
            case 1: // -y direction
                x = static_cast<float>(rand() % windowSize.x);
                y = -static_cast<float>(rand() % 200 + 100);
                break;
            case 2: // x direction
                x = static_cast<float>(windowSize.x) + static_cast<float>(rand() % 200 + 100);
                y = static_cast<float>(rand() % windowSize.y);
                break;
            case 3: // y direction
                x = static_cast<float>(rand() % windowSize.x);
                y = static_cast<float>(windowSize.y) + static_cast<float>(rand() % 200 + 100);
                break;
        }

        // Create and add a new enemy at the random coordinates
        enemies.emplace_back(enemyTexture, 50.0f, 100, 100.0f, 10, player);
        enemies.back().getSprite().setPosition(x, y);
    }


    // Remove a dead enemy from the vector
    void removeDeadEnemies() {
        // Iterate through the vector of enemies
        for (auto it = enemies.begin(); it != enemies.end(); ) {
            // Check if the enemy is dead
            if (it->getHealth() <= 0) {
                // Erase the enemy from the vector
                it = enemies.erase(it);
            } else {
                ++it;
            }
        }
    }

    // Draw all enemies
    void drawEnemies(sf::RenderWindow& window) {
        for (auto& enemy : enemies) {
            enemy.draw(window);
        }
    }


};




#endif //SFML_GAMEV3_SPAWNHANDLER_H
