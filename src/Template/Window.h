#ifndef WINDOW_H
#define WINDOW_H

#include "pch.h"
#include "Brique.h"
#include "Paddle.h"
#include "Ball.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Button.h"
#include "Explosion.h"
#include <memory>
#include "LevelConfig.h"
#include "MenuManager.h"
#include "SoundManager.h"
#include "AnimatedBackground.h"

class Window {
public:
    Window(int width, int height, const std::string& title);
    void run();

protected:
    void processEvents();
    void render();
    void update(float deltaTime);
    void updateBall(); // Ajoutez cette ligne
    void checkLevelCompletion();
    // Déclarez les fonctions pour les menus ici
    void drawGame(sf::RenderWindow& window);

    sf::RenderWindow window;
    std::vector<Brick> bricks;
    // Explosion* explosion;
    std::unique_ptr<Explosion> explosion;

    
    Paddle paddle;
    Ball balle; // Déclarez la balle ici si ce n'est pas déjà fait

    std::vector<PowerUp> powerUps;  // Liste de Power-Ups pour le niveau en cours
    int scoreMultiplier = 1;
    int paddleBoost;
    float powerUpTimer = 0.0f;

    void checkPowerUpCollection();
    void resetPowerUpEffect();

    sf::Text powerUpTimerText;

private:
    int currentLevel = 1;      // Niveau actuel
    bool gameCompleted = false; // Indicateur de fin de jeu
   /* bool isGameLost() const { return gameLost; }
    void setGameLost(bool state) { gameLost = state; }*/
    sf::Font font;

    enum class GameState {
        MainMenu,
        InGame,
        LevelMenu,
        VictoryMenu,
        GameOver
    };

    GameState gameState = GameState::MainMenu;

    bool ballVisible = true;
    bool gameLost = false;
    MenuManager menuManager;
    SoundManager soundManager;
    AnimatedBackground background;
};

#endif // WINDOW_H
