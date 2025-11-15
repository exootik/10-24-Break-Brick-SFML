#ifndef MENUMANAGER_H
#define MENUMANAGER_H
#include <SFML/Graphics.hpp>
#include "Button.h"

class MenuManager
{
public:
	MenuManager(sf::Font& font);

    void drawMainMenu(sf::RenderWindow& window);
    void drawLevelMenu(sf::RenderWindow& window);
    void drawVictoryMenu(sf::RenderWindow& window);
    void drawGameOverMenu(sf::RenderWindow& window);
    void drawScore(sf::RenderWindow& window);

    bool isButtonClicked(const std::string& buttonName, const sf::Vector2i& mousePos);
    Button* getButtonByName(const std::string& buttonName);
    static int score;
private:
    sf::Font font;
    sf::Text gameOverText, victoryText, nextLevelText, scoreText;
    Button startButton, nextLevelButton, quitButton, replayButton, retryButton;


};


#endif
