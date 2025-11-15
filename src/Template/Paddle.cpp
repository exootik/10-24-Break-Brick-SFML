#include "pch.h"
#include "Paddle.h"
#include "PowerUp.h"
#include <cstdlib>  // pour std::rand() et std::srand()
#include <ctime>    // pour std::time()
#include <cmath>

Paddle::Paddle(float windowWidth)
    : speed(1000.0f), windowWidth(windowWidth), isMoving(false), scaleFactor(0.1f), elapsedTime(0.0f) {
    originalWidth = 100.0f;
    shape.setSize(sf::Vector2f(originalWidth, 20.0f)); // Largeur et hauteur du paddle
    shape.setFillColor(sf::Color::White);
    shape.setPosition(windowWidth / 2 - shape.getSize().x / 2, 550); // Position initiale

    shape.setOutlineThickness(2); // Épaisseur de la lueur
    shape.setOutlineColor(sf::Color::Red);
}

// Implémentation de getShape
const sf::RectangleShape& Paddle::getShape() const {
    return shape;
}

void Paddle::update(float deltaTime) {
    isMoving = false;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        shape.move(-speed * deltaTime, 0);
        isMoving = true;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        shape.move(speed * deltaTime, 0);
        isMoving = true;
    }

    // Empêcher le paddle de sortir des bords
    if (shape.getPosition().x < 0) {
        shape.setPosition(0, shape.getPosition().y);
    }
    if (shape.getPosition().x + shape.getSize().x > windowWidth) {
        shape.setPosition(windowWidth - shape.getSize().x, shape.getPosition().y);
    }

    if (isMoving) {
        elapsedTime = 0.0f; // Réinitialiser le temps écoulé quand on bouge
        float scale = 1.0f + scaleFactor; // Applique un léger étirement horizontal
        shape.setScale(scale, 1.0f / scale); // Expansion horizontale et compression verticale
    }
    else {
        // Si le paddle s'arrête, ramener progressivement la taille à la normale
        elapsedTime += deltaTime;
        float normalizationSpeed = 5.0f; // Ajuste la vitesse de retour à la taille normale
        float scale = 1.0f + (scaleFactor * std::exp(-normalizationSpeed * elapsedTime));
        shape.setScale(scale, 1.0f / scale);
    }
}

void Paddle::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

float Paddle::getPositionX() const {
    return shape.getPosition().x;
}
float Paddle::getPositionY() const {
    return shape.getPosition().y;
}

void Paddle::resetPosition() {
    shape.setPosition(windowWidth / 2 - shape.getSize().x / 2, 550);
}

float Paddle::getWidth() const {
    return shape.getSize().x;
}

void Paddle::setColor() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));

    int red = std::rand() % 256;
    int green = std::rand() % 256;
    int blue = std::rand() % 256;

    shape.setFillColor(sf::Color(red, green, blue));

}


void Paddle::applySizeBoost(float boostAmount) {
    shape.setSize(sf::Vector2f(originalWidth + boostAmount, shape.getSize().y));
}

void Paddle::resetSize() {
    shape.setSize(sf::Vector2f(originalWidth, shape.getSize().y));
}