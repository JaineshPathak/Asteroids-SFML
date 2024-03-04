#include "EntityPowerup.h"

#include "Game.h"
#include "GameAssets.h"
#include "GameUtils.h"

EntityPowerup::EntityPowerup() :
	m_ElaspedTime(0.0f),
	m_ScaleFrequency(3.0f),

	m_Color1(sf::Color::Red),
	m_Color2(sf::Color::Yellow),
	m_CurrentColor(m_Color1)
{
	m_Texture = GameAssets::Get()->GetAsteroidTexture();

	m_Sprite.setTexture(m_Texture);
	m_Sprite.setColor(m_CurrentColor);

	Reset();
}

void EntityPowerup::Reset()
{
	if (!m_HasResetOrigin)
	{
		auto rect = m_Sprite.getGlobalBounds();
		m_Sprite.setOrigin(rect.width * 0.5f, rect.height * 0.5f);

		m_BoundingRadius = GameUtils::GetBoundingBoxRadius(rect.width, rect.height);

		m_HasResetOrigin = true;
	}

	m_ElaspedTime = 0.0f;
	m_CurrentColor = m_Color1;
}

void EntityPowerup::Update(float DeltaTime)
{
	m_ElaspedTime += DeltaTime;

	m_ScaleFactor = std::sinf(m_ElaspedTime * m_ScaleFrequency) * 0.25f + 2.0f * 0.5f;
	m_Sprite.setScale(m_ScaleFactor, m_ScaleFactor);

	m_ColorFactor = std::sinf(m_ElaspedTime * m_ScaleFrequency) + 2.0f * 0.5f;
	m_CurrentColor.r = (sf::Uint8)GameUtils::Lerp(m_Color1.r, m_Color2.r, m_ColorFactor);
	m_CurrentColor.g = (sf::Uint8)GameUtils::Lerp(m_Color1.g, m_Color2.g, m_ColorFactor);
	m_CurrentColor.b = (sf::Uint8)GameUtils::Lerp(m_Color1.b, m_Color2.b, m_ColorFactor);
	m_CurrentColor.a = 255;

	m_Sprite.setColor(m_CurrentColor);

	m_Position += m_Velocity;

	GameUtils::WrapCoordinates(m_Position.x, m_Position.y, m_Position.x, m_Position.y, (float)Game::s_MainWindow->getSize().x, (float)Game::s_MainWindow->getSize().y, m_BoundingRadius);

	m_Sprite.setPosition(m_Position);
}

void EntityPowerup::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite, states);
}
