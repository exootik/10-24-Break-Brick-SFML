#pragma once

class Paddle {
private:
    sf::RectangleShape shape;
    float speed;
    float windowWidth;
    // Attributs pour l'effet d'élasticité
    bool isMoving;
    float scaleFactor;
    float elapsedTime;
    float originalWidth;

public:
    Paddle(float windowWidth);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

    float getPositionX() const;
    float getPositionY() const;
    float getWidth() const;

    void resetPosition();
    void setColor();
    int paddleBoost;

    const sf::RectangleShape& getShape() const;
    void applySizeBoost(float boostAmount);
    void resetSize();
};

