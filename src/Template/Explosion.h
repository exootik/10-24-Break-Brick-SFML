#ifndef EXPLOSION_H
#define EXPLOSION_H

#include "pch.h"
#include <SFML/Graphics.hpp>
#include <vector>

class Explosion {
public:

    Explosion(const sf::Vector2f& position); // Assurez-vous que le constructeur existe
    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    bool isFinished();


private:
    std::vector<sf::CircleShape> particles;
    float duration; // Durée de vie de l'explosion
    float elapsedTime; // Temps écoulé depuis le début de l'explosion
};

#endif // EXPLOSION_H
