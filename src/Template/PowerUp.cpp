#include "pch.h"
#include "PowerUp.h"

PowerUp::PowerUp(Type type, const sf::Vector2f& position, sf::Texture& texture)
    : type(type), active(true), timer(0.0f), duration(10.0f) {
    if (type == Type::x2) {
        
        sprite.setTexture(texture);
        sprite.setPosition(position);
    }    
    if (type == Type::giant) {
        
        sprite.setTexture(texture);
        sprite.setPosition(position);
    }    
}


void PowerUp::reset() {
    active = true;      // Réactiver le Power-Up
    timer = 0.0f;       // Réinitialiser le timer
}


void PowerUp::applyEffect(int& scoreMultiplier, int& paddleBoost) {

    if (type == Type::x2) {
        scoreMultiplier = 2; // Multiplier les points par 2
    } 

    if (type == Type::giant) {
        paddleBoost = 600; 
    }
   
}

void PowerUp::resetEffect(int& scoreMultiplier, int& paddleBoost) {
    if (type == Type::x2) {
        scoreMultiplier = 1; // Réinitialiser le multiplicateur
    }

    if (type == Type::giant) {
        paddleBoost = 0;
    }
}

void PowerUp::update(float deltaTime) {
    if (!active) return;
    timer += deltaTime;
    if (timer >= duration) {
        active = false; // Fin de l'effet
    }
}

void PowerUp::draw(sf::RenderWindow& window) {
    if (active) {
        window.draw(sprite);
    }
}

bool PowerUp::isActive() const {
    return active;
}

void PowerUp::deactivate() {
    active = false;  // Désactiver le Power-Up
}

bool PowerUp::isCollected(const sf::FloatRect& playerBounds) const {
    return sprite.getGlobalBounds().intersects(playerBounds);
}

void PowerUp::setSize(float width, float height) {
    float scaleX = width / sprite.getLocalBounds().width;
    float scaleY = height / sprite.getLocalBounds().height;
    sprite.setScale(scaleX, scaleY); // Redimensionner en fonction de la taille voulue
}