#pragma once
#include "button.h"

Button::Button(std::wstring text, sf::Font& font, int textSize, sf::Color textColor,
    sf::Vector2f buttonSize, sf::Vector2f position, sf::Color buttonColor) {
    button.setSize(buttonSize);
    button.setPosition(position);
    button.setFillColor(buttonColor);
    button.setOutlineColor(sf::Color::White);
    button.setOutlineThickness(2.0f);

    buttonText.setString(text);
    buttonText.setFont(font);
    buttonText.setCharacterSize(textSize);
    buttonText.setFillColor(textColor);

    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    buttonText.setPosition(position.x + buttonSize.x / 2.0f, position.y + buttonSize.y / 2.0f);
}

Button::Button() {
    button.setOutlineColor(sf::Color::Cyan);
    button.setOutlineThickness(2.0f);
}

Button::~Button() {

};

sf::RectangleShape Button::getButton() {
    return button;
}

void Button::drawButton(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(buttonText);
}

std::wstring Button::getButtonText() {
    return buttonText.getString();
}

