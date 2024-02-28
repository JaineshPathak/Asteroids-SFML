#include "EntityBullet.h"

#include "Game.h"
#include "GameAssets.h"
#include "GameUtils.h"

EntityBullet::EntityBullet()
{
	m_Tag = "Projectile";

	m_Texture = GameAssets::Get()->GetAsteroidTexture();
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setColor(sf::Color::Yellow);

	Reset();
}

void EntityBullet::Reset()
{
	auto rect = m_Sprite.getGlobalBounds();
	m_Sprite.setOrigin(rect.width * 0.5f, rect.height * 0.5f);

	m_Sprite.setScale(m_Sprite.getScale() * 0.3f);

	m_Velocity = sf::Vector2f(0.0f, 0.0f);
}

void EntityBullet::Update(float DeltaTime)
{
	m_Position += m_Velocity;

	if (IsActive() && IsOutsideScreen(m_Position.x, m_Position.y, (float)Game::s_MainWindow->getSize().x, (float)Game::s_MainWindow->getSize().y))
		SetActive(false);

	m_Sprite.setPosition(m_Position);
}

void EntityBullet::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}

void EntityBullet::OnCollision(Entity* OtherEntity)
{
	//TODO: Asteroid Splitting
	//TODO: Player Score Increments
	if (OtherEntity->GetTag() == "Asteroid")
	{

	}
}
