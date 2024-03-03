#include "EntityExplosion.h"

#include "GameAssets.h"
#include "GameUtils.h"

EntityExplosion::EntityExplosion() :
	m_IsPlaying(false),
	m_ScaleTimeCurrent(0.0f),
	m_ScaleTime(0.5f),
	m_ScaleFactor(0.0f),

	m_StartColour(sf::Color::White),
	m_EndColour(sf::Color::Yellow),
	m_CurrentColour(m_StartColour)
{
	m_Texture = GameAssets::Get()->GetAsteroidTexture();

	m_Sprite.setTexture(m_Texture);
	m_Sprite.setColor(m_CurrentColour);

	Reset();
}

void EntityExplosion::Reset()
{
	if (!m_HasResetOrigin)
	{
		auto rect = m_Sprite.getGlobalBounds();
		m_Sprite.setOrigin(rect.width * 0.5f, rect.height * 0.5f);

		m_HasResetOrigin = true;
	}

	m_IsPlaying = false;
	m_ScaleFactor = 0.0f;
	m_ScaleTimeCurrent = 0.0f;

	m_Velocity = sf::Vector2f(0.0f, 0.0f);
	m_Sprite.setScale(sf::Vector2f(m_ScaleFactor, m_ScaleFactor));

	m_CurrentColour = m_StartColour;
	m_Sprite.setColor(m_CurrentColour);
}

void EntityExplosion::Update(float DeltaTime)
{
	if (m_IsPlaying)
	{
		m_ScaleTimeCurrent += DeltaTime;
		m_ScaleFactor = m_ScaleTimeCurrent / m_ScaleTime;

		if (m_ScaleTimeCurrent >= m_ScaleTime)
		{
			m_IsPlaying = false;
			SetActive(false);
		}

		m_Sprite.setScale(sf::Vector2f(m_ExplosionScaleMultiplier + (m_ScaleFactor * m_ExplosionScaleMultiplier), m_ExplosionScaleMultiplier + (m_ScaleFactor * m_ExplosionScaleMultiplier)));

		m_CurrentColour.r = (sf::Uint8)GameUtils::Lerp(m_StartColour.r, m_EndColour.r, m_ScaleFactor);
		m_CurrentColour.g = (sf::Uint8)GameUtils::Lerp(m_StartColour.g, m_EndColour.g, m_ScaleFactor);
		m_CurrentColour.b = (sf::Uint8)GameUtils::Lerp(m_StartColour.b, m_EndColour.b, m_ScaleFactor);
		m_CurrentColour.a = (sf::Uint8)GameUtils::Lerp(m_StartColour.a, 0.0f, m_ScaleFactor);
		
		m_Sprite.setColor(m_CurrentColour);
		//std::cout << (int)m_CurrentColour.a << std::endl;
	}

	m_Sprite.setPosition(m_Position);
}

void EntityExplosion::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}

void EntityExplosion::PlayExplosion(const float& explosionScaleMultiplier)
{
	m_ExplosionScaleMultiplier = explosionScaleMultiplier;
	m_IsPlaying = true;
}
