#include "EntityAsteroid.h"

#include "Game.h"
#include "GameAssets.h"
#include "GameUtils.h"

#include "EntitiesPool.h"

EntityAsteroid::EntityAsteroid() :
	m_Type(3),
	m_HasEnteredScreen(false)
{
	m_Tag = GameData::AsteroidTag;

	m_Texture = GameAssets::Get()->GetAsteroidTexture();
	
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setColor(sf::Color::White);

	m_Type = GameUtils::RandI(1, 4);

	Reset();
}

void EntityAsteroid::Reset()
{
	if (!m_HasResetOrigin)
	{
		auto rect = m_Sprite.getGlobalBounds();
		m_Sprite.setOrigin(rect.width * 0.5f, rect.height * 0.5f);

		m_BoundingRadius = GameUtils::GetBoundingBoxRadius(rect.width, rect.height);

		m_HasResetOrigin = true;
	}

	m_HasEnteredScreen = false;
	m_Sprite.setScale((float)m_Type, (float)m_Type);

	m_Velocity = sf::Vector2f(0.0f, 0.0f);
}

void EntityAsteroid::Update(float DeltaTime)
{
	m_Position += m_Velocity;

	if (!m_HasEnteredScreen && GameUtils::IsInsideScreen(m_Position.x, m_Position.y, (float)Game::s_MainWindow->getSize().x, (float)Game::s_MainWindow->getSize().y))
		m_HasEnteredScreen = true;
	
	if(m_HasEnteredScreen)
		GameUtils::WrapCoordinates(m_Position.x, m_Position.y, m_Position.x, m_Position.y, (float)Game::s_MainWindow->getSize().x, (float)Game::s_MainWindow->getSize().y, m_BoundingRadius);

	m_Sprite.setPosition(m_Position);
}

void EntityAsteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}

void EntityAsteroid::OnDisable()
{
	if (Game::Get() != nullptr)
		Game::Get()->OnAsteroidDestroyed(*this);
}

void EntityAsteroid::Split()
{
	//Already small, no more splitting required. Calls main game Class OnAsteroidDestroyed()
	if (m_Type == 1)
	{
		SetActive(false);
		OnDisable();
		return;
	}

	for (int i = 0; i < 2; i++)
	{
		EntityAsteroid* Rock = static_cast<EntityAsteroid*>(EntitiesPool::Get()->GetPooledEntity(EPT_Asteroid));
		if (Rock != nullptr)
		{
			Rock->SetActive(true);
			Rock->SetType(m_Type - 1);
			Rock->Reset();

			Rock->SetPosition(m_Position);

			float speedByType = (float)m_Type / 10.0f;

			sf::Vector2f newVel;
			newVel.x = GameUtils::RandF(-speedByType, speedByType);
			newVel.y = GameUtils::RandF(-speedByType, speedByType);

			Rock->SetCurrentVelocity(newVel);
		}
	}

	m_Type--;
	SetActive(false);
	//OnDisable();
}