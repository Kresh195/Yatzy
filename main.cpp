#pragma once
#include <iostream>
#include "GameMenu.h"
#include "Game.h"

int main()
{
    std::srand(std::time(0));
    float windowWidth = 1280;
    float windowHeight = 720;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), L"Покер на костях");
    sf::Image icon;
    if (!icon.loadFromFile("media/icon.png")) {
        return -1;
    }
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    std::cout << window.getSize().x << " " << window.getSize().y << std::endl;

    sf::Texture menuBackground;
    if (!menuBackground.loadFromFile("media/menu.png")) {
        std::cerr << "Failed to load background!" << std::endl;
    }
    sf::Texture gameBackground;
    if (!gameBackground.loadFromFile("media/game-background.png")) {
        std::cerr << "Failed to load background!" << std::endl;
    }
    sf::Texture rulesBackground;
    if (!rulesBackground.loadFromFile("media/wood.jpg")) {
        std::cerr << "Failed to load background!" << std::endl;
    }
    sf::Font font;
    if (!font.loadFromFile("fonts/Dust West Italic.otf")) {
        return -1;
    }

    sf::RectangleShape background(sf::Vector2f(windowWidth, windowHeight));
    sf::Color textColor = sf::Color(222, 181, 17);

    GameState gameState;

    GameMenu menu(window, font, textColor, gameState);
    menu.setMenuBackground(menuBackground);

    Game game(window, font, textColor, gameState);
    game.setGameBackground(gameBackground);
    
    background.setTexture(&rulesBackground);
    

    while (window.isOpen()) {
        GameState::state currentGameState = gameState.getCurrentState();
        switch (currentGameState) {
        case 0:
            menu.handleInput();
            menu.update();
            menu.draw(menuBackground);
            break;
        case 1:
            //Игра
            game.handleInput();
            game.update();
            game.draw(gameBackground);
            break;
        case 2:
            //Итоговый счёт
            break;
        case 3:
            //Меню настроек
            break;
        case 4:
            //Правила
            window.clear();
            window.draw(background);
            window.display();
            break;
        }
    }

    return 0;
}