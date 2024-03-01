#pragma once
#include <SFML/Graphics.hpp>

class EntityPlayer;
class GameUI
{
public:
	GameUI(sf::RenderWindow& mainWindow, EntityPlayer& mainPlayer);
	
	void Update();
	void Draw();

private:
	sf::RenderWindow& m_MainWindow;
	sf::Vector2f m_MainWindowDimensions;

	EntityPlayer& m_MainPlayer;

	sf::Text m_ScoreText;
	sf::Text m_LivesText;

	sf::Texture m_PlayerTexture;
	sf::Sprite m_PlayerSprite;

	sf::Font m_MainFont;
};