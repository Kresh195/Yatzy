#pragma once

#include <iostream>
#include "button.h"

Button::Button(std::wstring text, sf::Font& font, int textSize, sf::Color textColor,
    sf::Vector2f buttonSize, sf::Vector2f position) {
    button.setSize(buttonSize);
    button.setPosition(position);
    button.setFillColor(originalColor);
    button.setOutlineColor(sf::Color::Black);
    button.setOutlineThickness(2.0f);

    buttonText.setString(text);
    buttonText.setFont(font);
    buttonText.setCharacterSize(textSize);
    buttonText.setFillColor(textColor);

    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    buttonText.setPosition(position.x + buttonSize.x / 2.0f, position.y + buttonSize.y / 2.0f);
}

Button::Button(sf::Vector2f buttonSize, sf::Vector2f position, int buttondID) {
    button.setSize(buttonSize);
    button.setPosition(position);
    button.setFillColor(sf::Color(0, 0, 0, 0));
    this->buttonID = buttondID;
}

Button::Button(sf::Vector2f buttonSize, sf::Vector2f position) {
    button.setSize(buttonSize);
    button.setPosition(position);
    button.setFillColor(sf::Color(0, 0, 0, 0));
}

Button::~Button() {

};

sf::RectangleShape Button::getButton() {
    return button;
}

int Button::getButtonID() {
    return buttonID;
}

std::wstring Button::getButtonText() {
    return buttonText.getString();
}

bool Button::getActivity() {
    return activity;
}

void Button::setText(std::wstring text, sf::Font& font, int size, sf::Color color) {
    buttonText.setString(text);
    buttonText.setFillColor(color);
    buttonText.setFont(font);
    buttonText.setCharacterSize(size);

    sf::Vector2f position = button.getPosition();
    sf::Vector2f buttonSize = button.getSize();
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    buttonText.setPosition(position.x + buttonSize.x / 2.0f, position.y + buttonSize.y / 2.0f);
}

void Button::setText(std::wstring text) {
    buttonText.setString(text);
    sf::Vector2f position = button.getPosition();
    sf::Vector2f buttonSize = button.getSize();
    sf::FloatRect textBounds = buttonText.getLocalBounds();
    buttonText.setOrigin(textBounds.left + textBounds.width / 2.0f, textBounds.top + textBounds.height / 2.0f);
    buttonText.setPosition(position.x + buttonSize.x / 2.0f, position.y + buttonSize.y / 2.0f);
}

void Button::setTextColor(sf::Color color) {
    buttonText.setFillColor(color);
}

void Button::setOriginalColor() {
    button.setFillColor(originalColor);
}

void Button::setButtonTexture(sf::Texture& buttonTexture) {
    button.setFillColor(sf::Color::White);
    button.setTexture(&buttonTexture);
}

void Button::setActivity(bool activity) {
    this->activity = activity;
}

void Button::setButtonID(int id) {
    buttonID = id;
}

void Button::editOriginalColor(sf::Color color) {
    originalColor = color;
}

void Button::editDarkerColor(sf::Color color) {
    darkerColor = color;
}

void Button::drawButton(sf::RenderWindow& window) {
    window.draw(button);
    window.draw(buttonText);
}

void Button::shadeButton() {
    button.setFillColor(darkerColor);
}

bool Button::isClicked() {
    return buttonClicked;
}

void Button::click() {
    buttonClicked = true;
}
