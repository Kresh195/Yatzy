#pragma once

#include <iostream>
#include "GameMenu.h"

GameMenu::GameMenu(sf::RenderWindow& window, sf::Font& font, sf::Color textColor, GameState& currentGameState)
    : window(window), menuFont(font), currentGameState(currentGameState) {
    int textSize = 55;
    sf::Vector2f buttonSize = sf::Vector2f(200, 50);
    float windowWidth = window.getSize().x;
    float windowHeight = window.getSize().y;
    menuFont = font;

    sf::Vector2f playButtonPosition(windowWidth / 2 - 100, windowHeight * 3 / 4 - 100);
    menuButtons.emplace_back(L"Играть", font, textSize, textColor, buttonSize, playButtonPosition);

    sf::Vector2f rulesButtonPosition(windowWidth / 2 - 100, windowHeight * 3 / 4 - 35);
    menuButtons.emplace_back(L"Правила", font, textSize, textColor, buttonSize, rulesButtonPosition);

    sf::Vector2f exitButtonPosition(windowWidth / 2 - 100, windowHeight * 3 / 4 + 30);
    menuButtons.emplace_back(L"Выход", font, textSize, textColor, buttonSize, exitButtonPosition);
}

GameMenu::~GameMenu() {

}

void GameMenu::handleInput() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseMoved) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(window);
            for (auto& button : menuButtons) {
                if (button.getButton().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                    button.shadeButton();
                } 
                else {
                    button.setOriginalColor();
                }
            }
        }
        if (event.type == sf::Event::MouseButtonPressed) {
            if (event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                for (auto& button : menuButtons) {
                    if (button.getButton().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
                        std::cout << "Button is pressed! " << mousePos.x << " " << mousePos.y << std::endl;
                        if (button.getButtonText() == L"Играть") {
                            currentGameState.setCurrentState(GameState::Game);
                        }
                        else if (button.getButtonText() == L"Правила") {
                            currentGameState.setCurrentState(GameState::gameRules);
                        }
                        else if (button.getButtonText() == L"Выход") {
                            std::cout << "Game closed." << std::endl;
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
    window.clear();
    window.draw(this->menuBackground);
    for (auto& button : menuButtons) {
        button.drawButton(window);
    }
    window.display();
}

void GameMenu::setMenuFont(sf::Font menuFont) {
    this->menuFont = menuFont;
}

void GameMenu::setMenuBackground(sf::Texture menuBackground) {
    sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
    background.setTexture(&menuBackground);
    this->menuBackground = background;
}
