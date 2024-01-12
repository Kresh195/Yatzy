#pragma once
#include <SFML/Graphics.hpp>
#include <string>

class Button
{
public:
	Button(std::wstring text, sf::Font& font, int textSize, sf::Color textColor,
		sf::Vector2f buttonSize, sf::Vector2f position);

	Button(sf::Vector2f buttonSize, sf::Vector2f position, int buttonID);

	Button(sf::Vector2f buttonSize, sf::Vector2f position);

	~Button();

	int getButtonID();

	sf::RectangleShape getButton();

	std::wstring getButtonText();

	bool getActivity();

	void setText(std::wstring text, sf::Font& font, int size, sf::Color color);

	void setOriginalColor();

	void setButtonTexture(sf::Texture& buttonTexture);

	void setActivity(bool activity);

	void setButtonID(int id);

	void editOriginalColor(sf::Color color);

	void editDarkerColor(sf::Color color);

	void drawButton(sf::RenderWindow& window);

	void shadeButton();

	bool isClicked();

	void click();
private:
	sf::RectangleShape button;
	sf::Text buttonText;
	bool buttonClicked = false;
	sf::Color originalColor = sf::Color(0, 0, 0, 100);
	sf::Color darkerColor = sf::Color(0, 0, 0, 180);
	int buttonID;
	bool activity = true;
};
