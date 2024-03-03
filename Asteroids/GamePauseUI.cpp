#include "GamePauseUI.h"
#include "EntityPlayer.h"

GamePauseUI::GamePauseUI(sf::RenderWindow& renderWindow, EntityPlayer& mainPlayer) :
	GameIntroUI(renderWindow),
	m_MainPlayer(mainPlayer)
{
	m_TitleText.setString("PAUSED");
	m_TitleText.setOutlineColor(sf::Color::Red);
	m_TitleText.setOutlineThickness(2.0f);

	auto titleRect = m_TitleText.getGlobalBounds();
	m_TitleText.setOrigin(titleRect.width * 0.5f, titleRect.height * 0.5f);

	m_EnterToPlayText.setString("Press 'Enter' to Resume!");
	m_EnterToPlayText.setCharacterSize(40);

	auto playRect = m_EnterToPlayText.getGlobalBounds();
	m_EnterToPlayText.setOrigin(playRect.width * 0.5f, playRect.height * 0.5f);

	m_ScoreText.setFont(m_GameFont);
	m_ScoreText.setFillColor(sf::Color::Red);
}

PushdownState::PushdownResult GamePauseUI::OnUpdate(float dt, PushdownState** newState)
{
	m_TitleText.setPosition(m_MainWindowDimensions.x * 0.5f, m_MainWindowDimensions.y * 0.25f);
	m_EnterToPlayText.setPosition(m_MainWindowDimensions.x * 0.5f, m_MainWindowDimensions.y * 0.75f);

	m_ScoreText.setString("Score: " + std::to_string(m_MainPlayer.GetScoreCount()));
	auto scoreRect = m_ScoreText.getGlobalBounds();
	m_ScoreText.setOrigin(scoreRect.width * 0.5f, scoreRect.height * 0.5f);
	m_ScoreText.setPosition(m_MainWindowDimensions.x * 0.5f, m_MainWindowDimensions.y * 0.5f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter))
		return PushdownResult::PR_Pop;

	return PushdownResult::PR_NoChange;
}

void GamePauseUI::OnDraw()
{
	m_MainWindow.draw(m_TitleText);
	m_MainWindow.draw(m_EnterToPlayText);
	m_MainWindow.draw(m_ScoreText);
}
