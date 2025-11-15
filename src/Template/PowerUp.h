#ifndef POWERUP_H
#define POWERUP_H

#include "pch.h"
#include <SFML/Graphics.hpp>

class PowerUp {
public:
    enum class Type {
        x2,  
        giant
    };

    PowerUp(Type type, const sf::Vector2f& position, sf::Texture& texture);

    void reset();
    void applyEffect(int& scoreMultiplier, int& paddleBoost); // Appliquer le x2
    void resetEffect(int& scoreMultiplier, int& paddleBoost); // Réinitialiser l'effet

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);
    void deactivate();
    bool isActive() const;
    bool isCollected(const sf::FloatRect& playerBounds) const;
    void setSize(float width, float height);

private:
    Type type;
    sf::Sprite sprite;
    sf::Texture texture;
    bool active = true;
    float duration = 10.0f; // Durée d’effet
    float timer = 0.0f;
    int paddleBoost = 0;

};

#endif // POWERUP_H
