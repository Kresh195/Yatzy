#pragma once

#include "Button.h"

class GameMenu {
public:
    GameMenu(sf::RenderWindow& window, float windowWidth, float windowHeight, sf::Font& font);

    ~GameMenu();

    void handleInput();

    void update();

    void draw(sf::Texture menuBackground);

    void setMenuFont(sf::Font menuFont);

    void setMenuBackground(sf::Texture menuBackground);

private:
    float windowWidth;
    float windowHeight;
    sf::RenderWindow& window;
    std::vector<Button> menuButtons;
    sf::Font& menuFont;
    sf::Texture menuBackground;
};

