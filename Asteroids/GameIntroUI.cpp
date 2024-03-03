#include "GameIntroUI.h"

#include "Game.h"
#include "GameAssets.h"

GameIntroUI::GameIntroUI(sf::RenderWindow& renderWindow) :
	m_MainWindow(renderWindow)
{
	m_MainWindowDimensions.x = (float)m_MainWindow.getSize().x;
	m_MainWindowDimensions.y = (float)m_MainWindow.getSize().y;

	m_GameFont = GameAssets::Get()->GetGameFont();
	
	m_TitleText.setFont(m_GameFont);
	m_TitleText.setString("ASTEROIDS");
	m_TitleText.setFillColor(sf::Color::Black);
	m_TitleText.setOutlineColor(sf::Color::Yellow);
	m_TitleText.setOutlineThickness(2.0f);
	m_TitleText.setCharacterSize(80);

	auto titleRect = m_TitleText.getGlobalBounds();
	m_TitleText.setOrigin(titleRect.width * 0.5f, titleRect.height * 0.5f);

	m_EnterToPlayText.setFont(m_GameFont);
	m_EnterToPlayText.setString("Press Enter to Play!");
	m_EnterToPlayText.setCharacterSize(40);

	auto playRect = m_EnterToPlayText.getGlobalBounds();
	m_EnterToPlayText.setOrigin(playRect.width * 0.5f, playRect.height * 0.5f);

	m_ControlsText.setFont(m_GameFont);
	m_ControlsText.setString(m_ControlsStr);
	m_ControlsText.setCharacterSize(30);

	auto rect = m_ControlsText.getGlobalBounds();
	m_ControlsText.setOrigin(rect.width * 0.5f, rect.height * 0.5f);
}

PushdownState::PushdownResult GameIntroUI::OnUpdate(float DeltaTime, PushdownState** newState)
{
	m_TitleText.setPosition(m_MainWindowDimensions.x * 0.5f, m_MainWindowDimensions.y * 0.25f);
	m_EnterToPlayText.setPosition(m_MainWindowDimensions.x * 0.5f, m_MainWindowDimensions.y * 0.75f);
	m_ControlsText.setPosition(m_MainWindowDimensions.x * 0.5f, m_MainWindowDimensions.y * 0.5f);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scan::Enter))
	{
		*newState = new Game(m_MainWindow);
		return PushdownResult::PR_Push;
	}

	return PushdownResult::PR_NoChange;
}

void GameIntroUI::OnDraw()
{
	m_MainWindow.draw(m_TitleText);
	m_MainWindow.draw(m_EnterToPlayText);
	m_MainWindow.draw(m_ControlsText);
}
