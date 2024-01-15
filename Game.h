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
    std::vector<int> diceValues;

    sf::Font& gameFont;
    sf::RectangleShape gameBackground;

    int playerCount = 2;
    std::vector<Player> players;
    playerColors currentPlayerColor = green;
    Player* currentPlayer;

    bool isTurnEnded = false;
    bool isStarted = false;

    sf::Color textColor;
    sf::Text playerTurnText;
    
    int gameRound = 0;
    const int combinationCount = 13;

    std::vector<Button> tableCellButtons;
    std::vector<Button> selectedCells;
    std::vector<Button> tableTexts;
};
