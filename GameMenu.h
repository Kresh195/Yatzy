#pragma once

#include "Button.h"
#include "GameState.h"


class GameMenu {
public:
    GameMenu(sf::RenderWindow& window, sf::Font& font, sf::Color textColor, GameState& currentGameState);

    ~GameMenu();

    void handleInput();

    void update();

    void draw(sf::Texture menuBackground);

    void setMenuFont(sf::Font menuFont);

    void setMenuBackground(sf::Texture menuBackground);

private:
    sf::RenderWindow& window;
    std::vector<Button> menuButtons;
    sf::Font& menuFont;
    sf::RectangleShape menuBackground;
    GameState& currentGameState;
    sf::Color textColor;
};

