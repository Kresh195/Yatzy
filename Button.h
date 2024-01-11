#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
	Button(std::wstring text, sf::Font& font, int textSize, sf::Color textColor,
		sf::Vector2f buttonSize, sf::Vector2f position);

	Button();

	~Button();

	void drawButton(sf::RenderWindow& window);

	sf::RectangleShape getButton();

	std::wstring getButtonText();

	void shadeButton();

	void setOriginalColor();

private:
	sf::RectangleShape button;
	sf::Text buttonText;
	bool isClicked = false;
	sf::Color originalColor = sf::Color(0, 0, 0, 100);
	sf::Color darkerColor = sf::Color(0, 0, 0, 180);
};
