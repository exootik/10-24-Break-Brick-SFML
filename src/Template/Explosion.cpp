#include "pch.h"
#include "Explosion.h"

Explosion::Explosion(const sf::Vector2f& position)
    : duration(1.0f), elapsedTime(0.0f) {
    // Créez quelques particules pour l'explosion
    for (int i = 0; i < 30; ++i) {
        sf::CircleShape particle(5.0f); // Rayon de chaque particule
        particle.setFillColor(sf::Color::Yellow); // Couleur des particules
        particle.setPosition(position);

        // Ajouter une position aléatoire pour chaque particule
        float offsetX = static_cast<float>((rand() % 50) - 25); // Entre -25 et 25
        float offsetY = static_cast<float>((rand() % 50) - 25); // Entre -25 et 25
        particle.setPosition(position.x + offsetX, position.y + offsetY);

        particles.push_back(particle);
    }
}

void Explosion::update(float deltaTime) {
    elapsedTime += deltaTime;

    // Vous pouvez également mettre à jour les particules ici si vous le souhaitez
    for (auto& particle : particles) {
        particle.move(0, -50 * deltaTime); // Déplacez les particules vers le haut
    }
}

void Explosion::draw(sf::RenderWindow& window) {
    for (const auto& particle : particles) {
        window.draw(particle);
    }
}

bool Explosion::isFinished() {
    particles.clear(); // Efface les particules
    return true;
}
