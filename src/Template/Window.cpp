#include "pch.h"
#include "Window.h"
#include "Ball.h"
#include "Brique.h"
#include "Paddle.h"
#include "LevelConfig.h"
#include "Button.h"
#include "Explosion.h"
#include "MenuManager.h"
#include <SFML/Audio.hpp>
#include <memory> // Pas nécessaire si vous n'utilisez plus std::make_unique
#include <SFML/System.hpp>

sf::Clock delayForExplosion;
bool waiting = true;


Window::Window(int width, int height, const std::string& title)

    : window(sf::VideoMode(width, height), title), paddle(width), balle(20, { 400, 500 }), explosion(nullptr), menuManager(font), soundManager(), background(window.getSize()){ // Initialisation de la balle et explosion ici

    window.setVerticalSyncEnabled(true);

    powerUpTimerText.setFont(font);
    powerUpTimerText.setCharacterSize(24);
    powerUpTimerText.setFillColor(sf::Color::White);

}

void Window::run() {
    sf::Clock clock;

    while (window.isOpen()) {
        float deltaTime = clock.restart().asSeconds();

        processEvents();
        update(deltaTime);
        render();
    }
}

void Window::updateBall() {
    // Déplacez la balle seulement si le jeu n'est pas perdu
    if (!gameLost) {
        balle.move();
        

        // Vérifiez les collisions avec les briques
        for (auto it = bricks.begin(); it != bricks.end(); ) {
            if (balle.checkBounds(1280, 720, *it, paddle)) {
              soundManager.playBufferInGame();
              Brick::Type brickType = it->getType(); // Récupérer le type de la brique

              // Vérifier le type de brique et adapter le comportement
              if (brickType == Brick::Type::Classique) {
                  menuManager.score += 10 * scoreMultiplier;
                  it = bricks.erase(it); // Supprimer la brique de type classique
              }
              if (brickType == Brick::Type::Bonus) {
                  menuManager.score += 10 * scoreMultiplier;
                  it = bricks.erase(it); // Supprimer la brique de type classique
              }
              if (brickType == Brick::Type::Resistante) {
                  it->setType(Brick::Type::Classique);
                  it->setColor(sf::Color::White);
                  ++it;
              }
            }
            else {
                ++it; // Passe à la brique suivante
            }
        }
        /*if (balle.checkBounds(1280, 720, bricks , paddle)) {
            gameLost = true;
        }*/
        if (balle.checkBoundsWithGround(paddle) == true) {
            gameLost = true;
        }
    }
}

void Window::update(float deltaTime) {
    if (gameState == GameState::InGame) {

        background.update(deltaTime);
        paddle.update(deltaTime);
        updateBall(); // Met à jour la balle et vérifie les collisions avec les briques

        // Vérifier si toutes les briques sont détruites pour passer au niveau suivant
        if (bricks.empty()) {
            checkLevelCompletion();
            if (currentLevel < levelConfigs.size()) {
                balle.reset({ 400, 500 }, { 2.0f, -2.0f });
            }
            paddle.resetPosition();
        }

        // Vérifiez la collecte des Power-Ups
        checkPowerUpCollection();

        // Mettre à jour le timer du Power-Up x2 si actif
        if (powerUpTimer > 0.0f) {
            powerUpTimer -= deltaTime;
            if (powerUpTimer <= 0.0f) {
                resetPowerUpEffect(); // Réinitialiser le multiplicateur de points
            }
        }

        // Mettre à jour les Power-Ups actifs
        for (auto& powerUp : powerUps) {
            powerUp.update(deltaTime);
        }
        
        // Vérifier si le jeu est perdu
        if (gameLost) {
            soundManager.stopInGameSound();
            soundManager.playEndGameSound();
            /*bool waiting = true;*/
            if (!explosion) {
                explosion = std::make_unique<Explosion>(balle.getPosition()); // Créer l'explosion
                ballVisible = false; // Masquer la balle
                delayForExplosion.restart();
            }
            explosion->update(deltaTime); // Mettre à jour l'explosion
            if (waiting && delayForExplosion.getElapsedTime().asSeconds() >= 1.0f) {
                explosion->isFinished();
                gameState = GameState::GameOver;
                waiting = false; // Fin de l'attente
                std::cout << "Condition de delai executé";
            } 
            return; // Sortir si le jeu est perdu
        }

        if (powerUpTimer > 0.0f) {
            powerUpTimer -= deltaTime;
            powerUpTimerText.setString("PowerUp End: " + std::to_string(static_cast<int>(powerUpTimer)));
            powerUpTimerText.setPosition(10, 660); // Position en haut à gauche, ajustez si nécessaire
        }
    }
}


void Window::checkLevelCompletion() {
    currentLevel++;
    soundManager.stopInGameSound();
    soundManager.playEndGameSound();
    if (currentLevel < levelConfigs.size()) {
        // Passer au menu des niveaux
        gameState = GameState::LevelMenu;
    }
    else {
        // Si tous les niveaux sont terminés, passer à l'écran de victoire
        gameState = GameState::VictoryMenu;
        
    }
}

void Window::render() {
    window.clear();
    background.draw(window);

    switch (gameState) {
    case GameState::MainMenu:
        menuManager.drawMainMenu(window);
        break;
    case GameState::InGame:
        drawGame(window);
        break;
    case GameState::LevelMenu:
        menuManager.drawLevelMenu(window);
        break;
    case GameState::VictoryMenu:
        menuManager.drawVictoryMenu(window);
        break;
    case GameState::GameOver:
        menuManager.drawGameOverMenu(window);
        break;
    }

    if (powerUpTimer > 0.0f) {
        window.draw(powerUpTimerText);
    }

    if (explosion) {
        explosion->draw(window); // Dessiner l'explosion si elle n'est pas finie
    }

    for (auto& powerUp : powerUps) {
        if (powerUp.isActive()) {
            
            
            powerUp.draw(window);
        }
    }

    window.display();
}

void Window::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            window.close();
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            switch (gameState) {
            case GameState::MainMenu:
                if (menuManager.isButtonClicked("start", mousePos)) {
                    gameState = GameState::InGame;
                    initializeLevel(currentLevel, bricks, powerUps);
                    MenuManager::score = 0; // Réinitialise le score
                    gameLost = false;
                    soundManager.stopEndGameSound();
                    soundManager.playInGameSound();
                }
                break;

            case GameState::LevelMenu:
                if (menuManager.isButtonClicked("nextLevel", mousePos)) {
                    gameState = GameState::InGame;
                    initializeLevel(currentLevel, bricks, powerUps);
                    balle.reset({ 400, 500 }, { 2.0f, -2.0f }); // Réinitialiser la balle
                    soundManager.stopEndGameSound();
                    soundManager.playInGameSound();
                }
                else if (menuManager.isButtonClicked("quit", mousePos)) {
                    window.close();
                }
                break;

            case GameState::VictoryMenu:
                if (menuManager.isButtonClicked("replay", mousePos)) {
                std::cout << "VictoryMenu ouvert";
                    gameState = GameState::MainMenu;
                    currentLevel = 0;
                    MenuManager::score = 0;
                    soundManager.stopEndGameSound();
                    soundManager.playInGameSound();
                }
                else if (menuManager.isButtonClicked("quit", mousePos)) {
                    window.close();
                }
                break;

            case GameState::GameOver:
                if (menuManager.isButtonClicked("retryLevel", mousePos)) {
                    gameState = GameState::InGame;
                    initializeLevel(currentLevel, bricks, powerUps);
                    ballVisible = true;
                    gameLost = false;
                    MenuManager::score = 0;
                    // Réinitialiser l'explosion et l'animation
                    explosion = nullptr;             // Réinitialise l'explosion
                    waiting = true;                  // Réinitialise l'état d'attente
                    balle.reset({ 600, 500 }, { 2.0f, -2.0f });
                    soundManager.stopEndGameSound();
                    soundManager.playInGameSound();
                    paddle.resetPosition();
                }
                else if (menuManager.isButtonClicked("quit", mousePos)) {
                    window.close();
                }
                break;
            }
        }
    }
}

void Window::drawGame(sf::RenderWindow& window) {
    for (const auto& brick : bricks) {
        window.draw(brick.getShape());
    }

    if (ballVisible) {
        balle.draw(window); // Ne dessine la balle que si elle est visible
    }

    paddle.draw(window);

    menuManager.drawScore(window);
}

void Window::checkPowerUpCollection() {
    for (auto& powerUp : powerUps) {
        if (powerUp.isCollected(paddle.getShape().getGlobalBounds()) && powerUp.isActive()) {
            powerUp.applyEffect(scoreMultiplier, paddleBoost);
            paddle.applySizeBoost(paddleBoost);
            powerUpTimer = 10.0f; // Activer le multiplicateur pour 10 secondes
            powerUp.deactivate(); // Désactiver le Power-Up une fois collecté
        }
    }
}

void Window::resetPowerUpEffect() {
    scoreMultiplier = 1;  // Réinitialiser le multiplicateur
    paddleBoost = 1;
    paddle.resetSize();
}

// Ajoutez un destructeur pour gérer la mémoire
//Window::~Window() {
//    delete explosion; // Libérez la mémoire allouée pour explosion
//}

