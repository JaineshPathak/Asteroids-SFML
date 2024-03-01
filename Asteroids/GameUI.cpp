#include "GameUI.h"

#include "EntityPlayer.h"
#include "GameAssets.h"

#include <iostream>

GameUI::GameUI(sf::RenderWindow& mainWindow, EntityPlayer& mainPlayer) :
	m_MainWindow(mainWindow),
	m_MainPlayer(mainPlayer)
{
	m_MainWindowDimensions.x = (float)m_MainWindow.getSize().x;
	m_MainWindowDimensions.y = (float)m_MainWindow.getSize().y;

	m_MainFont = GameAssets::Get()->GetGameFont();
	m_MainFont.setSmooth(true);

	m_LivesText.setFont(m_MainFont);
	m_LivesText.setFillColor(sf::Color::Blue);

	m_ScoreText.setFont(m_MainFont);
	m_ScoreText.setFillColor(sf::Color::Red);

	m_PlayerTexture = GameAssets::Get()->GetPlayerTexture();
	m_PlayerSprite.setTexture(m_PlayerTexture);
	m_PlayerSprite.setColor(sf::Color::Blue);
	//m_PlayerSprite.setScale(0.75f, 0.75f);

	//auto rect = m_PlayerSprite.getGlobalBounds();
	//m_PlayerSprite.setOrigin(0.0f, rect.height);

	//sf::Font gameFont = GameAssets::Get()->GetGameFont();
	//std::cout << gameFont.getInfo().family << std::endl;

	std::cout << "Game UI: Ready!" << std::endl;
}

void GameUI::Update()
{
	m_LivesText.setPosition({ 10.0f, 10.0f });
	m_LivesText.setString("Lives: ");

	m_ScoreText.setPosition({ m_MainWindowDimensions.x - m_ScoreText.getGlobalBounds().width - 10.0f, 10.0f});
	m_ScoreText.setString("Score: " + std::to_string(m_MainPlayer.GetScoreCount()));
}

void GameUI::Draw()
{
	const float startX = m_LivesText.getGlobalBounds().getSize().x + 10.0f;
	const float startY = 10.0f;
	const float spacing = 10.0f;
	for (int i = 0; i < m_MainPlayer.GetLivesCount(); i++)
	{
		m_PlayerSprite.setPosition(startX + (m_PlayerSprite.getLocalBounds().width + spacing) * i, startY);
		m_MainWindow.draw(m_PlayerSprite);
	}

	m_MainWindow.draw(m_ScoreText);
	m_MainWindow.draw(m_LivesText);
}
