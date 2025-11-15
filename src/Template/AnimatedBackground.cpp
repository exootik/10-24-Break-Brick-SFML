#include "pch.h"
#include "AnimatedBackground.h"

AnimatedBackground::AnimatedBackground(const sf::Vector2u& windowSize)
    : startColor(100, 100, 255), // Couleur initiale (bleu clair)
    endColor(255, 100, 100),   // Couleur finale (rouge clair)
    animationTime(10.0f),      // Durée d'un cycle complet d'animation (en secondes)
    currentTime(0.0f) {
    background.setSize(sf::Vector2f(windowSize.x, windowSize.y));
    background.setPosition(0, 0);
    background.setFillColor(startColor);
}

void AnimatedBackground::update(float deltaTime) {
    // Incrémente le temps courant
    currentTime += deltaTime;

    // Si on dépasse le temps d'animation, on inverse la direction du dégradé
    if (currentTime > animationTime) {
        currentTime = 0.0f;
        std::swap(startColor, endColor); // Inverse les couleurs
    }

    // Calcul de la progression de l’animation
    float t = currentTime / animationTime;

    // Calcul de la couleur intermédiaire en fonction du temps
    sf::Uint8 red = static_cast<sf::Uint8>((1 - t) * startColor.r + t * endColor.r);
    sf::Uint8 green = static_cast<sf::Uint8>((1 - t) * startColor.g + t * endColor.g);
    sf::Uint8 blue = static_cast<sf::Uint8>((1 - t) * startColor.b + t * endColor.b);

    background.setFillColor(sf::Color(red, green, blue));
}

void AnimatedBackground::draw(sf::RenderWindow& window) {
    window.draw(background);
}