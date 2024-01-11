#pragma once

#include <iostream>
#include "GameMenu.h"
#include "Button.h"

GameMenu::GameMenu(sf::RenderWindow& window, float windowWidth, float windowHeight, sf::Font& font)
    : window(window), menuFont(font) {
    sf::Color textColor(222, 181, 17);
    sf::Color buttonColor = sf::Color::Black;
    int textSize = 55;
    sf::Vector2f buttonSize = sf::Vector2f(200, 50);
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    menuFont = font;

    sf::Vector2f playButtonPosition(windowWidth / 2 - 100, windowHeight * 3 / 4 - 100);
    menuButtons.emplace_back(L"Играть", font, textSize, textColor, buttonSize, playButtonPosition, buttonColor);

    sf::Vector2f rulesButtonPosition(windowWidth / 2 - 100, windowHeight * 3 / 4 - 35);
    menuButtons.emplace_back(L"Правила", font, textSize, textColor, buttonSize, rulesButtonPosition, buttonColor);

    sf::Vector2f exitButtonPosition(windowWidth / 2 - 100, windowHeight * 3 / 4 + 30);
    menuButtons.emplace_back(L"Выход", font, textSize, textColor, buttonSize, exitButtonPosition, buttonColor);
}

GameMenu::~GameMenu() {

}

void GameMenu::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                for (auto& button : menuButtons) {
                    if (button.getButton().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << "Button is pressed! " << mousePos.x << " " << mousePos.y << std::endl;
                        if (button.getButtonText() == L"Играть") {
                            
                        }
                        else if (button.getButtonText() == L"Правила") {
                            
                        }
                        else if (button.getButtonText() == L"Выход") {
                            window.close();  
                        }
                    }
                }
            }
        }
    }
}

void GameMenu::update() {
    
    // Реализация метода update
}

void GameMenu::draw(sf::Texture menuBackground) {
    sf::Font nameFont;
    if (!nameFont.loadFromFile("fonts/Dust West Italic.otf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }
    sf::RectangleShape background(sf::Vector2f(windowWidth, windowHeight));
    background.setTexture(&menuBackground);

    window.clear();
    window.draw(background);
    for (auto& button : menuButtons) {
        button.drawButton(window);
    }
    window.display();
}

void GameMenu::setMenuFont(sf::Font menuFont) {
    this->menuFont = menuFont;
}

void GameMenu::setMenuBackground(sf::Texture menuBackground) {
    this->menuBackground = menuBackground;
}
