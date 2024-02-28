#include "EntityAsteroid.h"

#include "Game.h"
#include "GameAssets.h"
#include "GameUtils.h"

EntityAsteroid::EntityAsteroid() :
	m_Type(3)
{
	m_Tag = GameData::AsteroidTag;

	m_Texture = GameAssets::Get()->GetAsteroidTexture();
	
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setColor(sf::Color::White);

	Reset();
}

void EntityAsteroid::Reset()
{
	auto rect = m_Sprite.getGlobalBounds();
	m_Sprite.setOrigin(rect.width * 0.5f, rect.height * 0.5f);

	m_Sprite.setScale(m_Sprite.getScale() * (float)m_Type);

	m_Velocity = sf::Vector2f(0.0f, 0.0f);
}

void EntityAsteroid::Update(float DeltaTime)
{
	m_Position += m_Velocity;

	GameUtils::WrapCoordinates(m_Position.x, m_Position.y, m_Position.x, m_Position.y, (float)Game::s_MainWindow->getSize().x, (float)Game::s_MainWindow->getSize().y);

	m_Sprite.setPosition(m_Position);
}

void EntityAsteroid::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}

void EntityAsteroid::OnCollision(Entity* OtherEntity)
{
}

void EntityAsteroid::Split()
{
}
