#include "pch.h"
#include "Brique.h"
#include "random"

Brick::Brick(const sf::Vector2f& position, Type type) : type(type) {
    shape.setSize(sf::Vector2f(60, 20)); // Taille de la brique
    shape.setPosition(position);
    bounds = shape.getGlobalBounds();

    // Attribuer une couleur en fonction du type de brique
    switch (type) {
    case Type::Classique:
        shape.setFillColor(sf::Color::White);
        break;
    case Type::Bonus:
        shape.setFillColor(sf::Color::Blue);
        break;
    case Type::Resistante:
        shape.setFillColor(sf::Color::Black);
        break;
    }
}

Brick::~Brick() {}
// Implémentation de getShape
const sf::RectangleShape& Brick::getShape() const {
    return shape;
}

void Brick::setColor(const sf::Color& color) {
    shape.setFillColor(color);
}

void Brick::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(shape, states);
}

void Brick::createBrickGrid(std::vector<Brick>& bricks, int rows, int cols, float offsetX, float offsetY, int brickWidth, int brickHeight, int brickSizeX, int brickSizeY) {
    // Calculer la largeur totale de la grille pour la centrer
    float totalWidth = cols * (brickWidth + offsetX) - offsetX;
    float startX = (1280 - totalWidth) / 2;

    // Configurer le générateur de nombres aléatoires
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 2); // Pour générer 0, 1 ou 2

    // Positionnement et dimensionnement des briques
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            sf::Vector2f position(startX + j * (brickWidth + offsetX), i * (brickHeight + offsetY));

            // Générer un type aléatoire
            Type randomType = static_cast<Type>(dist(gen));

            // Créer une nouvelle brique du type aléatoire
            Brick brick(position, randomType);


            // Définir la taille de la brique en fonction des nouveaux paramètres `brickSizeX` et `brickSizeY`
            brick.shape.setSize(sf::Vector2f(brickSizeX, brickSizeY));

            // Ajouter la brique au vecteur
            bricks.push_back(brick);
        }
    }
}


std::pair<bool, Brick::Side> Brick::checkCollision(const sf::FloatRect& ballBounds) const {
    auto currentBounds = shape.getGlobalBounds(); // Utilisation des bounds actuels

    if (!currentBounds.intersects(ballBounds)) {
        return { false, Side::Top };
    }

    float overlapTop = currentBounds.top + currentBounds.height - ballBounds.top;
    float overlapBottom = ballBounds.top + ballBounds.height - currentBounds.top;
    float overlapLeft = currentBounds.left + currentBounds.width - ballBounds.left;
    float overlapRight = ballBounds.left + ballBounds.width - currentBounds.left;

    if (overlapTop < overlapBottom && overlapTop < overlapLeft && overlapTop < overlapRight) {
        return { true, Side::Top };
    }
    else if (overlapBottom < overlapTop && overlapBottom < overlapLeft && overlapBottom < overlapRight) {
        return { true, Side::Bottom };
    }
    else if (overlapLeft < overlapRight && overlapLeft < overlapTop && overlapLeft < overlapBottom) {
        return { true, Side::Left };
    }
    else {
        return { true, Side::Right };
    }
}
