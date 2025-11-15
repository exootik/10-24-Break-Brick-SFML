#ifndef BRICK_H
#define BRICK_H

#include "pch.h"

class Brick : public sf::Drawable {
public:
    enum class Side {
        Top,
        Bottom,
        Left,
        Right
    };

    enum class Type {
        Classique,
        Bonus,
        Resistante
    };

    Brick(const sf::Vector2f& position, Type type);
    ~Brick();
    void setColor(const sf::Color& color);
    const sf::RectangleShape& getShape() const;
    static void createBrickGrid(std::vector<Brick>& bricks, int rows, int cols, float offsetX, float offsetY, int brickWidth, int brickHeight, int brickSizeX, int brickSizeY);
    std::pair<bool, Side> checkCollision(const sf::FloatRect& ballBounds) const;

    // Définir l'opérateur == pour comparer les briques
    bool operator==(const Brick& other) const {
        return shape.getPosition() == other.shape.getPosition() &&
            shape.getSize() == other.shape.getSize();
    }
    Type getType() const{
        return type;
    }
    void setType(Type newType) {
        type = newType;
    }


protected:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::RectangleShape shape;
    sf::FloatRect bounds;
    Type type;
};

#endif // BRICK_H
