#include "EntityBullet.h"

#include "Game.h"
#include "GameAssets.h"
#include "GameUtils.h"

#include "EntityAsteroid.h"
#include "EntityPlayer.h"

EntityBullet::EntityBullet()
{
	m_Tag = GameData::BulletTag;

	m_Texture = GameAssets::Get()->GetAsteroidTexture();
	
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setColor(sf::Color::Yellow);

	Reset();
}

void EntityBullet::Reset()
{
	if (!m_HasResetOrigin)
	{
		auto rect = m_Sprite.getGlobalBounds();
		m_Sprite.setOrigin(rect.width * 0.5f, rect.height * 0.5f);

		m_HasResetOrigin = true;
	}

	m_Sprite.setScale(m_Sprite.getScale() * 0.3f);

	m_Velocity = sf::Vector2f(0.0f, 0.0f);
}

void EntityBullet::Update(float DeltaTime)
{
	m_Position += m_Velocity;

	if (IsActive() && GameUtils::IsOutsideScreen(m_Position.x, m_Position.y, (float)Game::s_MainWindow->getSize().x, (float)Game::s_MainWindow->getSize().y))
		SetActive(false);

	m_Sprite.setPosition(m_Position);
}

void EntityBullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}

void EntityBullet::OnCollision(Entity* OtherEntity)
{
	//Is it an Asteroid?
	EntityAsteroid* rock = dynamic_cast<EntityAsteroid*>(OtherEntity);
	if (rock)
	{
		if (m_EntityPlayerOwner)
			m_EntityPlayerOwner->AddScore(rock->GetType());

		rock->Split();

		SetActive(false);
	}
}

void EntityBullet::SetOwner(Entity* newOwner)
{
	Entity::SetOwner(newOwner);

	if (m_EntityOwner != nullptr)
		m_EntityPlayerOwner = (EntityPlayer*)m_EntityOwner;
}
