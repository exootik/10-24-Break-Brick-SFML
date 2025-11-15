#include "pch.h"
#include "MenuManager.h"

int MenuManager::score = 0;
MenuManager::MenuManager(sf::Font& font) : font(font){
    // Initialisation des boutons
    startButton = Button({ 200, 50 }, { 540, 360 }, "Start", font);
    nextLevelButton = Button({ 200, 50 }, { 540, 360 }, "Next Level", font);
    quitButton = Button({ 200, 50 }, { 540, 440 }, "Quit", font);
    replayButton = Button({ 200, 50 }, { 540, 360 }, "Replay", font);
    retryButton = Button({ 200, 50 }, { 540, 360 }, "Retry", font);

    gameOverText.setFont(font);
    gameOverText.setString("Défaite");
    gameOverText.setCharacterSize(36);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition(570, 260);

    victoryText.setFont(font);
    victoryText.setString("Victoire");
    victoryText.setCharacterSize(36);
    victoryText.setFillColor(sf::Color::Green);
    victoryText.setPosition(570, 260);

    nextLevelText.setFont(font);
    nextLevelText.setString("Félicitations, vous pouvez faire le prochain niveau");
    nextLevelText.setCharacterSize(24);
    nextLevelText.setFillColor(sf::Color::White);
    nextLevelText.setPosition(350, 260);

    scoreText.setFont(font);
    scoreText.setString("Score: " + std::to_string(score));
    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition(1080, 660);
}

void MenuManager::drawMainMenu(sf::RenderWindow& window) {
    startButton.draw(window);
}
void MenuManager::drawLevelMenu(sf::RenderWindow& window) {
    window.draw(nextLevelText);
    nextLevelButton.draw(window);
    quitButton.draw(window);
}
void MenuManager::drawVictoryMenu(sf::RenderWindow& window) {
    window.draw(victoryText);
    replayButton.draw(window);
    quitButton.draw(window);
}
void MenuManager::drawGameOverMenu(sf::RenderWindow& window) {
    window.draw(gameOverText);
    retryButton.draw(window);
    quitButton.draw(window);
}
void MenuManager::drawScore(sf::RenderWindow& window) {
    scoreText.setString("Score: " + std::to_string(score));
    window.draw(scoreText);
}
Button* MenuManager::getButtonByName(const std::string& buttonName) {
    if (buttonName == "start") return &startButton;
    if (buttonName == "quit") return &quitButton;
    if (buttonName == "nextLevel") return &nextLevelButton;
    if (buttonName == "replay") return &replayButton;
    if (buttonName == "retryLevel") return &retryButton;

    return nullptr; // Retourne nullptr si le nom ne correspond à aucun bouton
}

bool MenuManager::isButtonClicked(const std::string& buttonName, const sf::Vector2i& mousePos) {
    Button* button = getButtonByName(buttonName);
    return button ? button->isClicked(mousePos) : false;
}
