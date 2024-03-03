#pragma once
#include "GameIntroUI.h"

#include <SFML/Graphics.hpp>

class EntityPlayer;
class GamePauseUI : public GameIntroUI
{
public:
	GamePauseUI(sf::RenderWindow& renderWindow, EntityPlayer& mainPlayer);

	virtual PushdownResult OnUpdate(float dt, PushdownState** newState) override;
	virtual void OnDraw() override;

private:
	EntityPlayer& m_MainPlayer;
	sf::Text m_ScoreText;
};