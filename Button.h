#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
	Button(std::wstring text, sf::Font& font, int textSize, sf::Color textColor,
		sf::Vector2f buttonSize, sf::Vector2f position, sf::Color buttonColor);

	Button();

	~Button();

	void drawButton(sf::RenderWindow& window);

	sf::RectangleShape getButton();

	std::wstring getButtonText();

private:
	sf::RectangleShape button;
	sf::Text buttonText;
	bool isClicked = false;
};
