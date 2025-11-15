#pragma once
#include "pch.h"
#include <SFML/Graphics.hpp>

class AnimatedBackground {
public:
    AnimatedBackground(const sf::Vector2u& windowSize);

    void update(float deltaTime);
    void draw(sf::RenderWindow& window);

private:
    sf::RectangleShape background;
    sf::Color startColor;
    sf::Color endColor;
    float animationTime;
    float currentTime;
};
