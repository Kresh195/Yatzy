#pragma once

#include "Button.h"
#include "GameState.h"
#include "Dice.h"
#include "Player.h"

class Game
{
public:
    Game(sf::RenderWindow& window,  sf::Font& gameFont, sf::Color textColor, GameState& currentGameState);

    ~Game();

    void handleInput();

    void update();

    void draw(sf::Texture gameBackground);

    void setGameFont(sf::Font gameFont);

    void setGameBackground(sf::Texture gameBackground);
private:
    sf::RenderWindow& window;
    GameState& currentGameState;

    std::vector<Button> gameButtons;
    std::vector<Button> diceButtons;

    std::vector<sf::RectangleShape> diceLocks;
    sf::Texture diceLockTexture;

    std::vector<Dice> diceSet;
    std::vector<sf::Texture> diceTextures;

    sf::Font& gameFont;
    sf::RectangleShape gameBackground;

    int playerCount = 2;
    std::vector<Player> players;
    playerColors currentPlayerColor = green;
    Player currentPlayer = Player(green);

    bool isTurnEnded = false;

    sf::Color textColor;
    sf::Text playerTurnText;
    
};
