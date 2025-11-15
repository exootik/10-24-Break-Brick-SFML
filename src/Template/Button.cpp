#include "pch.h"
#include "Button.h"

Button::Button() {
    // Configurations par défaut du bouton (par exemple, taille et couleur neutre)
    background.setSize({ 100, 50 }); // Taille par défaut arbitraire
    background.setFillColor(sf::Color::Blue);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);
}

Button::Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text, sf::Font& font) {
    background.setSize(size);
    background.setPosition(position);
    background.setFillColor(sf::Color::Blue);

    font.loadFromFile("../../../src/Template/Asset/font.ttf"); // Assurez-vous de mettre le bon chemin vers votre police
    buttonText.setFont(font);
    buttonText.setString(text);
    buttonText.setCharacterSize(24);
    buttonText.setFillColor(sf::Color::White);

    // Centrer le texte dans le bouton
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setPosition(
        position.x + (size.x - textBounds.width) / 2,
        position.y + (size.y - textBounds.height) / 2
    );
}

void Button::draw(sf::RenderWindow& window) {
    window.draw(background);
    window.draw(buttonText);
}

bool Button::isClicked(const sf::Vector2i& mousePos) const {
    return background.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos));
}