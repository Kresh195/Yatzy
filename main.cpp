#pragma once
#include <iostream>
#include "Button.h"
#include "GameMenu.h"
#include "GameState.h"

int main()
{
    float windowWidth = 1280;
    float windowHeight = 720;
    sf::RenderWindow window(sf::VideoMode(windowWidth, windowHeight), L"����� �� ������");
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
    sf::Font nameFont;
    if (!nameFont.loadFromFile("fonts/Dust West Italic.otf")) {
        return -1;
    }
    sf::Font font;
    if (!font.loadFromFile("fonts/PressStart2P-Regular.ttf")) {
        return -1;
    }

    sf::RectangleShape background(sf::Vector2f(windowWidth, windowHeight));

    GameMenu menu(window, windowWidth, windowHeight, nameFont);

    menu.setMenuBackground(menuBackground);

    GameState gameState;

    while (window.isOpen()) {
        GameState::state currentGameState = gameState.getCurrentState();
        switch (currentGameState) {
        case 0:
            menu.handleInput();
            menu.update();
            menu.draw(menuBackground);
            break;
        case 1:
            //����
            break;
        case 2:
            //�������� ����
            break;
        case 3:
            //���� ��������
            break;
        case 4:
            //�������
            break;
        }
    }

    return 0;
}