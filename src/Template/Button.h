#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    Button();

    Button(const sf::Vector2f& size, const sf::Vector2f& position, const std::string& text, sf::Font& font);
    void draw(sf::RenderWindow& window);
    bool isClicked(const sf::Vector2i& mousePos) const;

private:
    sf::RectangleShape background;
    sf::Text buttonText;
    sf::Font font;
};


#endif // !BUTTON_H