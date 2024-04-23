#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "ShootingSystemV2.h"
#include "SpawnHandler.h"
#include <vector>

int main() {
    srand(static_cast<unsigned int>(time(nullptr)));

    // Create the window
    sf::RenderWindow window(sf::VideoMode(1000, 800), "SFML TopDownShooter v2");

    // Load background texture
    sf::Texture backgroundTexture;
    if (!backgroundTexture.loadFromFile("../grass.png")) {
        // Handle error loading texture
        return EXIT_FAILURE;
    }

    // Create background sprite
    sf::Sprite backgroundSprite(backgroundTexture);
    // Scale background sprite to fit the window
    backgroundSprite.setScale(window.getSize().x / backgroundSprite.getLocalBounds().width, window.getSize().y / backgroundSprite.getLocalBounds().height);

    // Load player texture
    sf::Texture playerTexture;
    if (!playerTexture.loadFromFile("../Top_Down_Survivor/rifle/idle/survivor-idle_rifle_0.png")) {
        // Handle error loading texture
        return EXIT_FAILURE;
    }

    // Load enemy texture
    sf::Texture enemyTexture;
    if (!enemyTexture.loadFromFile("../export/skeleton-attack_0.png")) {
        // Handle error loading texture
        return EXIT_FAILURE;
    }

    // Create player object
    Player player(playerTexture, 150.0f, 100, 360.0f);
    player.getSprite().setPosition(window.getSize().x / 2, window.getSize().y / 2);
    // Set player size to 0.5, 0.5
    //player.getSprite().setScale(0.5f, 0.5f);

    // Create container containing all enemy objects
    std::vector<Enemy> enemies;
    // Create enemy object
    //Enemy enemy(enemyTexture, 50.0f, 100, 100.0f, 10, player);
    //enemies.push_back(enemy);
    //enemies[0].getSprite().setScale(0.5f, 0.5f);

    // Create spawn handler
    SpawnHandler spawnHandler(enemies, enemyTexture, player, sf::seconds(1.0f));

    ShootingSystemV2 shootingSystemV2(player.getSprite(), 500.0, 700.0f);

    sf::Clock clock;
    sf::Time elapsedTime;

    // Aiming variables
    //bool isAiming = false;
    //sf::View normalView = window.getDefaultView();
    //sf::View zoomedView = normalView;
    //zoomedView.zoom(2.0f); // Zoom factor for aiming


    // Main loop
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        // Handle events
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            // Toggle aiming when right mouse button is pressed
            //if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Right)
            //{
            //    isAiming = true;
            //}

            // Return to normal view when right mouse button is released
            //if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Right)
            //{
            //    isAiming = false;
            //}
        }

        // Set the appropriate view based on aiming status
        //if (isAiming) {
        //    window.setView(zoomedView);
        //} else {
        //    window.setView(normalView);
        //}

        // Handle shooting event
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            shootingSystemV2.shootBullet(window);
        }

        // Update entities
        player.update(window, dt);
        //enemies[0].update(window, dt);
        shootingSystemV2.updateBullets(dt);
        shootingSystemV2.checkBulletEnemyCollision(enemies); // Check collisions after updating bullets

        // Update spawn handler
        spawnHandler.update(window,dt);
        spawnHandler.removeDeadEnemies();

        // Set the view center to the player's position
        sf::View view = window.getView();
        view.setCenter(player.getSprite().getPosition());
        window.setView(view);

        // Clear the window
        window.clear();

        // Draw background
        window.draw(backgroundSprite);

        player.draw(window);
        //enemies[0].draw(window);
        spawnHandler.drawEnemies(window);

        shootingSystemV2.drawLineToMouse(window);
        shootingSystemV2.drawBullets(window);

        // Display the window
        window.display();
    }

    return EXIT_SUCCESS;
}

