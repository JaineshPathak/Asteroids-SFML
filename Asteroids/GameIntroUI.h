#pragma once
#include "PushdownState.h"

#include <SFML/Graphics.hpp>

class GameIntroUI : public PushdownState
{
public:
	GameIntroUI(sf::RenderWindow& renderWindow);

	virtual PushdownResult OnUpdate(float dt, PushdownState** newState) override;
	virtual void OnDraw() override;

protected:
	sf::RenderWindow& m_MainWindow;

	sf::Vector2f m_MainWindowDimensions;
	sf::Font m_GameFont;

	sf::Text m_TitleText;
	sf::Text m_EnterToPlayText;

private:
	sf::String m_ControlsStr{"W - Thrust\nA,D - Turn\nSpace - Shoot"};
	sf::Text m_ControlsText;
};