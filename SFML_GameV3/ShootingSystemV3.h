

#ifndef SFML_GAMEV3_SHOOTINGSYSTEMV3_H
#define SFML_GAMEV3_SHOOTINGSYSTEMV3_H

#include <SFML/Graphics.hpp>
#include "BulletV2.h"
#include "Enemy.h"
#include <vector>

class ShootingSystemV3 {
private:
    sf::RenderWindow& window;
    std::vector<BulletV2> bullets;
    std::vector<Enemy>& enemiesContainer;
public:
    ShootingSystemV3(sf::RenderWindow& window, std::vector<Enemy>& enemies) : window(window), enemiesContainer(enemies) {}

    void shootBullet(const sf::Texture& bulletTexture, const sf::Vector2f& position, const sf::Vector2f& direction, float speed) {
        bullets.emplace_back(bulletTexture, position, direction, speed);
    }

    void update(float deltaTime) {
        for (auto it = bullets.begin(); it != bullets.end();) {
            it->update(deltaTime);

            // Check intersection with enemies or other objects
            for (auto& enemy : enemiesContainer) {
                if (intersectsRay(*it, enemy)) {
                    // Handle collision with enemy
                    enemy.takeDamage(1); // Example: decrease enemy health
                    it = bullets.erase(it);
                    break;
                }
            }

            if (it != bullets.end()) {
                ++it;
            }
        }
    }

    bool intersectsRay(const BulletV2& bullet, Enemy& enemy) {
        // Define the ray
        sf::Vector2f rayStart = bullet.getPosition() + sf::Vector2f(bullet.getSprite().getGlobalBounds().width / 2, bullet.getSprite().getGlobalBounds().height / 2);
        sf::Vector2f rayDirection = enemy.getSprite().getPosition() - rayStart;
        float rayLength = sqrt(rayDirection.x * rayDirection.x + rayDirection.y * rayDirection.y);
        rayDirection /= rayLength; // Normalize direction vector

        // Check intersection with enemy hitbox
        return bullet.getSprite().getGlobalBounds().intersects(enemy.getSprite().getGlobalBounds());
    }



    void draw() {
        for (auto& bullet : bullets) {
            bullet.draw(window);
        }
    }
};



#endif //SFML_GAMEV3_SHOOTINGSYSTEMV3_H
