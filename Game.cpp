#pragma once

#include <iostream>
#include "Game.h"
#include "Yatzy.h"

Game::Game(sf::RenderWindow& window, sf::Font& gameFont, sf::Color textColor, GameState& currentGameState)
	: window(window), gameFont(gameFont), currentGameState(currentGameState) {
	float windowWidth = window.getSize().x;
	float windowHeight = window.getSize().y;
	sf::Vector2f diceSize = sf::Vector2f(80, 80);
	sf::Vector2f diceLockSize = sf::Vector2f(40, 40);
	this->textColor = textColor;
	sf::Texture diceLockTexture;
	if (!diceLockTexture.loadFromFile("media/lock.png")) {
		std::cerr << "Failed to load dice lock texture!";
	}
	this->diceLockTexture = diceLockTexture;

	sf::RectangleShape diceLock;
	diceLock.setSize(diceLockSize);
	/*diceLock.setSize(sf::Vector2f(diceSize.x * 0.9, diceSize.y * 0.9));*/
	for (int i = 0; i < 5; i++) {
		float y, x = windowWidth / 4 - 190 + 120 * i;
		if (i % 2 == 1) {
			y = windowHeight * 3 / 5 - 150;
		}
		else {
			y = windowHeight * 3 / 5;
		}
		sf::Vector2f DicePosition(x, y);
		sf::Vector2f diceLockPosition(DicePosition.x + diceSize.x * 0.65, DicePosition.y + diceSize.y * 0.75);
		diceLock.setFillColor(sf::Color(0, 0, 0, 190));
		diceLock.setPosition(diceLockPosition);

		diceLocks.emplace_back(diceLock);
		diceButtons.emplace_back(diceSize, DicePosition, i+90);
	}

	for (int i = 0; i < 6; i++) {
		sf::Texture diceTexture;
		if (!diceTexture.loadFromFile("media/" + std::to_string(i+1) + ".png")) {
			std::cerr << "Failed to load dice texture!";
		}
		diceTextures.emplace_back(diceTexture);
	}

	sf::Vector2f rollButtonSize = sf::Vector2f(210, 95);
	sf::Vector2f rollButtonPosition(windowWidth / 4 - 15, windowHeight * 3 / 4 + 20);
	Button rollButton(L"Бросок", gameFont, 63, textColor, rollButtonSize, rollButtonPosition);
	rollButton.setButtonID(111);
	gameButtons.emplace_back(rollButton);
	
	sf::Vector2f cellSize = sf::Vector2f(59, 33);
	float xCellCoord = 1108;
	float yCellCoord = 104;
	int cellID = 0;
	for (int i = 0; i < 13; i++) {
		for (int j = 0; j < 2; j++) {
			cellID += 1;
			sf::Vector2f cellPosition = sf::Vector2f(xCellCoord, yCellCoord);
			Button tableCell(cellSize, cellPosition, cellID);
			tableCell.editOriginalColor(sf::Color(0, 0, 0, 0));
			tableCell.editDarkerColor(sf::Color(0, 0, 0, 80));
			gameButtons.emplace_back(tableCell);
			xCellCoord += 61;
		}
		if (i == 5 ) {
			yCellCoord += 78;
		}
		else if (i == 10) {
			yCellCoord += 2;
		}
		xCellCoord = 1108;
		yCellCoord += 34;
	}
	

	for (int i = 0; i < playerCount; i++) {
		playerColors color = static_cast<playerColors>(i);
		players.emplace_back(color);
	}

	for (auto& player : players) {
		std::cout << player.getPlayerColor() << std::endl;
	}


	playerTurnText = sf::Text(L"Ход зеленого игрока", gameFont, 75);
	playerTurnText.setFillColor(textColor);
	playerTurnText.setPosition(sf::Vector2f(windowWidth / 9, 15));
}

Game::~Game() {

}

void Game::handleInput() {
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();

		if (isTurnEnded) {
			isTurnEnded = false;
			for (auto& button : gameButtons) {
				if (button.getButtonID() == 111) {
					button.setActivity(true);
					break;
				}
			}
			for (auto& dice : diceSet) {
				dice.setLock(false);
			}
			currentPlayer.resetRolls();
			currentPlayerColor = static_cast<playerColors>((currentPlayerColor + 1) % playerCount);
			currentPlayer = players[currentPlayerColor];
			switch (currentPlayerColor)
			{
			case green:
				playerTurnText.setString(L"Ход зеленого игрока");
				break;
			case red:
				playerTurnText.setString(L"Ход красного игрока");
				break;
			case blue:
				playerTurnText.setString(L"Ход синего игрока");
				break;
			case yellow:
				playerTurnText.setString(L"Ход жёлтого игрока");
				break;
			}
		}
		if (event.type == sf::Event::MouseMoved) {
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			for (auto& button : gameButtons) {
				int buttonID = button.getButtonID();
				if (buttonID > 0 && buttonID <= 15 * playerCount) {
					if (button.isClicked() || currentPlayer.getRollsLeft() == 3) {
						button.setActivity(false);
					}
					else {
						if ((buttonID - 1) % playerCount == currentPlayerColor) {
							button.setActivity(true);
						}
						else {
							button.setActivity(false);
						}
					}
				}
				if (button.getButton().getGlobalBounds().contains(mousePos.x, mousePos.y) && button.getActivity()) {
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
				//std::cout << mousePos.x << " " << mousePos.y << std::endl;
				for (auto& button : gameButtons) {
					if (button.getButton().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
						//std::cout << "Button is pressed! " << mousePos.x << " " << mousePos.y << std::endl;
						int buttonID = button.getButtonID();
						if ((buttonID > 0) && (buttonID <= 15 * playerCount) 
							&& currentPlayer.getRollsLeft() < 3 && !button.isClicked()) {
							std::cout << buttonID % playerCount << " " << currentPlayerColor << std::endl;
							if ((buttonID - 1) % playerCount == currentPlayerColor && (buttonID > 0)
								&& (buttonID <= 15 * playerCount)) {
								button.setText(std::to_wstring(buttonID), gameFont, 20, sf::Color::Magenta);
								button.click();
								isTurnEnded = true;
							}
						}
						if (button.getButtonText() == L"Бросок" && button.getActivity()) {
							if (currentPlayer.getRollsLeft() == 3) {
								for (int diceNumber = 0; diceNumber < 5; diceNumber++) {
									Dice dice;
									dice.rollDice();
									int diceScore = dice.getValue();
									diceButtons[diceNumber].setButtonTexture(diceTextures[diceScore - 1]);
									diceSet.emplace_back(dice);
								}
							}
							else {
								for (int diceNumber = 0; diceNumber < 5; diceNumber++) {
									Dice dice = diceSet[diceNumber];
									if (!dice.isLocked()) {
										dice.rollDice();
										int diceScore = dice.getValue();
										diceButtons[diceNumber].setButtonTexture(diceTextures[diceScore - 1]);
										/*diceSet[diceNumber] = ;*/
									}
								}
							}
							currentPlayer.rolled();
							std::cout << "Rolls left: " << currentPlayer.getRollsLeft() << std::endl;
							if (currentPlayer.getRollsLeft() == 0) {
								button.setActivity(false);
							}
						}
					}
				}
				for (auto& button : diceButtons) {
					if (button.getButton().getGlobalBounds().contains(mousePos.x, mousePos.y) && currentPlayer.getRollsLeft() != 3) {
						int diceNumber = button.getButtonID() - 90;
						diceSet[diceNumber].changeLock();
						if (diceSet[diceNumber].isLocked()) {
							diceButtons[1].getButton().setSize(sf::Vector2f(100, 100));
							diceLocks[diceNumber].setTexture(&diceLockTexture);
							std::cout << "Dice " << diceNumber + 1 << " locked!" << std::endl;

						}
						else {
							diceButtons[1].getButton().setSize(sf::Vector2f(80, 80));
							std::cout << "Dice " << diceNumber + 1 << " unlocked!" << std::endl;
						}
					}
				}
			}
		}
	}
}

void Game::update() {

}

void Game::draw(sf::Texture gameBackground){
	window.clear();
	window.draw(this->gameBackground);
	window.draw(playerTurnText);
	for (auto& button : diceButtons) {
		button.drawButton(window);
	}
	for (int i = 0; i < 5; i++) {
		if (currentPlayer.getRollsLeft() != 3 && diceSet[i].isLocked())
			window.draw(diceLocks[i]);
	}
	for (auto& button : gameButtons) {
		if (!(button.getButtonID() == 111 && currentPlayer.getRollsLeft() == 0))
			button.drawButton(window);
	}
	window.display();
}

void Game::setGameFont(sf::Font gameFont){

}

void Game::setGameBackground(sf::Texture gameBackground){
	sf::RectangleShape background(sf::Vector2f(window.getSize().x, window.getSize().y));
	background.setTexture(&gameBackground);
	this->gameBackground = background;
}
