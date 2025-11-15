#ifndef BALL_H
#define BALL_H

#include "pch.h"
#include "Brique.h"
#include "Paddle.h"

class Ball {
public:
    Ball(float radius, const sf::Vector2f& position);
    ~Ball();
    void draw(sf::RenderWindow& window);
    void move();
    bool checkBounds(int windowWidth, int windowHeight, Brick& brick, Paddle& paddle);
    bool checkBoundsWithGround(Paddle& paddle);
    bool isGameLost() const; // Méthode pour vérifier si le jeu est perdu
    void reset(const sf::Vector2f& newPosition, const sf::Vector2f& newVelocity);
    sf::Vector2f getPosition() const { return shape.getPosition(); }
    sf::Vector2f getVelocity() const { return velocity; }
    void setVelocity(float vx, float vy) { velocity = { vx, vy }; }

private:
    sf::CircleShape shape;
    sf::Vector2f velocity;
};

#endif // BALL_H


