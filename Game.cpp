#pragma once

#include <iostream>
#include "Game.h"
#include "CalculateScore.h"

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
	for (int playerNumber = 0; playerNumber < playerCount; playerNumber++) {
		for (int combinationCellNumber = 0; combinationCellNumber < combinationCount; combinationCellNumber++) {
			cellID += 1;
			sf::Vector2f cellPosition = sf::Vector2f(xCellCoord, yCellCoord);
			Button tableCell(cellSize, cellPosition, cellID);
			tableCell.editOriginalColor(sf::Color(0, 0, 0, 0));
			tableCell.editDarkerColor(sf::Color(0, 0, 0, 80));
			tableCellButtons.emplace_back(tableCell);

			yCellCoord += 34;
			if (combinationCellNumber == 5) {
				yCellCoord += 78;
			}
			else if (combinationCellNumber == 10) {
				yCellCoord += 2;
			}
		}
		yCellCoord = 104;
		xCellCoord += 61;
	}

	for (int i = 0; i < playerCount; i++) {
		playerColors color = static_cast<playerColors>(i);
		players.emplace_back(color);
	}
	currentPlayer = &players[currentPlayerColor];

	xCellCoord = 1108;
	for (int i = 0; i < 2; i++) {
		yCellCoord = 315;
		for (int j = 0; j < 3; j++) {
			if (j == 2) {
				yCellCoord = 626;
				cellSize = sf::Vector2f(59, 57);
			}
			else {
				cellSize = sf::Vector2f(59, 33);
			}
			sf::Vector2f tableTextPosition = sf::Vector2f(xCellCoord, yCellCoord);
			Button tableText(cellSize, tableTextPosition);
			tableText.setText(L"", gameFont, 35, textColor);
			tableText.setActivity(false);
			if (j != 1) {
				tableText.setText(L"0");
			}
			yCellCoord += 34;
			tableTexts.emplace_back(tableText);
		}
		xCellCoord += 61;
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
		if (gameRound == 13) { //конец игры
			if (players[0].getScore() > players[1].getScore())
				playerTurnText.setString(L"Победа зелёного игрока!");
			else
				playerTurnText.setString(L"Победа красного игрока!");
		}
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
			currentPlayer->resetRolls();
			currentPlayerColor = static_cast<playerColors>((currentPlayerColor + 1) % playerCount);
			currentPlayer = &players[currentPlayerColor];
			if (currentPlayerColor == 0) //конец игры
				gameRound += 1;
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
			for (auto& button : tableCellButtons) {
				int buttonID = button.getButtonID();
				if (button.isClicked() || currentPlayer->getRollsLeft() == 3) {
					button.setActivity(false);
				}
				else {
					if ((buttonID - 1) / combinationCount == currentPlayerColor) {
						button.setActivity(true);
					}
					else {
						button.setActivity(false);
					}
				}
				if (button.getButton().getGlobalBounds().contains(mousePos.x, mousePos.y) && button.getActivity()) {
					button.shadeButton();
				}
				else {
					button.setOriginalColor();
				}
			}
			for (auto& button : gameButtons) {
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
				for (auto& button : tableCellButtons) {
					if (button.getButton().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
						int buttonID = button.getButtonID();
						if (currentPlayer->getRollsLeft() < 3 && !button.isClicked()
							&& (buttonID - 1) / combinationCount == currentPlayerColor) {
							button.setTextColor(textColor);
							button.click();
							int points = std::stoi(button.getButtonText());
							currentPlayer->increaseScore(points);
							if ((buttonID - 1) % combinationCount < 6) {
								currentPlayer->increaseBonusSum(points);
								tableTexts[0 + currentPlayerColor * 3].setText(std::to_wstring(currentPlayer->getBonusSum()));
								if (currentPlayer->checkBonus()) {
									tableTexts[1 + currentPlayerColor * 3].setText(std::to_wstring(35));
									currentPlayer->increaseScore(35);
									currentPlayer->recieveBonus();
								}
							}
							tableTexts[2 + currentPlayerColor * 3].setText(std::to_wstring(currentPlayer->getScore()));
							isTurnEnded = true;
							for (auto& cellButton : tableCellButtons) {
								if (!cellButton.isClicked()) {
									cellButton.setText(L"");
								}
							}
						}
					}
				}
				for (auto& button : gameButtons) {
					if (button.getButton().getGlobalBounds().contains(mousePos.x, mousePos.y)) {
						int buttonID = button.getButtonID();
						if (button.getButtonText() == L"Бросок" && button.getActivity()) {
							if (currentPlayer->getRollsLeft() == 3) {
								for (int diceNumber = 0; diceNumber < 5; diceNumber++) {
									Dice dice;
									dice.rollDice();
									int diceScore = dice.getValue();
									diceButtons[diceNumber].setButtonTexture(diceTextures[diceScore - 1]);
									diceSet.emplace_back(dice);
									if (isStarted) {
										diceSet[diceNumber] = dice;
									}
									else {
										diceSet.emplace_back(dice);
										isStarted = true;
									}
								}
							}
							else {
								for (int diceNumber = 0; diceNumber < 5; diceNumber++) {
									Dice dice = diceSet[diceNumber];
									if (!dice.isLocked()) {
										dice.rollDice();
										int diceScore = dice.getValue();
										diceButtons[diceNumber].setButtonTexture(diceTextures[diceScore - 1]);
										diceSet[diceNumber] = dice;
									}
								}
							}
							currentPlayer->rolled();
							std::cout << "Rolls left: " << currentPlayer->getRollsLeft() << std::endl;
							if (currentPlayer->getRollsLeft() == 0) {
								button.setActivity(false);
							}
							for (int i = 0; i < 5; i++) {
								int value = diceSet[i].getValue();
								diceValues.emplace_back(value);
							}
							CalculateScore diceSetScore(diceValues);
							std::vector<int> DiceValuesPoints = diceSetScore.getDiceValuesPoints();
							std::vector<int> combinationsPoints = diceSetScore.getCombinationsPoints();
							for (int i = 0; i < combinationCount; i++) {
								int cellID = i + currentPlayerColor * combinationCount;
								if (!tableCellButtons[cellID].isClicked()) {
									int points = combinationsPoints[i];
									tableCellButtons[cellID].setText(std::to_wstring(points), gameFont, 35, sf::Color::Red);
								}
							}
							int i = 1;
							for (auto& valueSum : DiceValuesPoints) {
								std::cout << "sum of " << i << " = " << valueSum << std::endl;
								i++;
							}
							std::cout << "3 of a kind = " << diceSetScore.getThreeOfAKindScore() << std::endl;
							std::cout << "4 of a kind = " << diceSetScore.getFourOfAKindScore() << std::endl;
							std::cout << "chance = " << diceSetScore.getChanceScore() << std::endl;
							std::cout << "full house = " << diceSetScore.checkFullHouse() << std::endl;
							std::cout << "small straight = " << diceSetScore.checkSmallStraight() << std::endl;
							std::cout << "large straight = " << diceSetScore.checkLargeStraight() << std::endl;
							std::cout << "YATZY = " << diceSetScore.checkYatzy() << std::endl;
							std::cout << std::endl << std::endl;
							diceValues.clear();
						}
					}
				}
				for (auto& button : diceButtons) {
					if (button.getButton().getGlobalBounds().contains(mousePos.x, mousePos.y) && currentPlayer->getRollsLeft() != 3) {
						int diceNumber = button.getButtonID() - 90;
						diceSet[diceNumber].changeLock();
						if (diceSet[diceNumber].isLocked()) {
							diceButtons[1].getButton().setSize(sf::Vector2f(100, 100));
							diceLocks[diceNumber].setTexture(&diceLockTexture);

						}
						else {
							diceButtons[1].getButton().setSize(sf::Vector2f(80, 80));
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
		if (currentPlayer->getRollsLeft() != 3 && diceSet[i].isLocked())
			window.draw(diceLocks[i]);
	}
	for (auto& button : gameButtons) {
		if (!(button.getButtonID() == 111 && currentPlayer->getRollsLeft() == 0))
			button.drawButton(window);
	}
	for (auto& button : tableCellButtons) {
		button.drawButton(window);
	}
	for (auto& tableText : tableTexts) {
		tableText.drawButton(window);
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
