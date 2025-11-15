#include "pch.h"
#include "Ball.h"
#include "Window.h"

Ball::Ball(float radius, const sf::Vector2f& position)
    : shape(radius), velocity(2.0f, -2.0f) {
    shape.setFillColor(sf::Color::Green);
    shape.setPosition(position);
}
Ball::~Ball() {}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

void Ball::move() {
    shape.move(velocity);
}

bool Ball::checkBounds(int windowWidth, int windowHeight, Brick& brick, Paddle& paddle) {
    sf::Vector2f position = shape.getPosition();
    float radius = shape.getRadius();

    if (shape.getGlobalBounds().intersects(paddle.getShape().getGlobalBounds())) {
        velocity.y = -velocity.y;
        shape.setPosition(position.x, position.y - 5);
        paddle.setColor();
    }

    // Collision axe X
    if (position.x < 0) { // Bord gauche
        velocity.x = -velocity.x;
        shape.setPosition(0, position.y);
    }
    else if (position.x + radius * 2 > windowWidth) { // Bord droit
        velocity.x = -velocity.x;
        shape.setPosition(windowWidth - radius * 2, position.y);
    }

    // Collision axe Y
    if (position.y < 0) { // Bord supérieur
        velocity.y = -velocity.y;
        shape.setPosition(position.x, 0);
    }

    // Vérification des collisions avec les briques
    auto [isCollision, collisionSide] = brick.checkCollision(shape.getGlobalBounds());
    if (isCollision) {
        switch (collisionSide) {
        case Brick::Side::Top:
        case Brick::Side::Bottom:
            velocity.y = -velocity.y;
            break;
        case Brick::Side::Left:
        case Brick::Side::Right:
            velocity.x = -velocity.x;
            break;
        }
        return true; // Collision détectée
    }
    return false; // Pas de collision
}

bool Ball::checkBoundsWithGround(Paddle& paddle) {
    sf::Vector2f position = shape.getPosition();
    if (position.y > paddle.getPositionY() + 100 ) {
        std::cout << "perdu" << std::endl;
        return true;  // Retourne true pour signaler que le jeu est perdu
    }
    return false;
}

bool Ball::isGameLost() const {
    return true;
}

void Ball::reset(const sf::Vector2f& newPosition, const sf::Vector2f& newVelocity) {
    shape.setPosition(newPosition);
    velocity = newVelocity;
     // Réinitialise le statut de jeu perdu pour le nouveau niveau
}
