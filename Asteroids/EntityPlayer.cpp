#include "EntityPlayer.h"

#include "EntityBullet.h"
#include "Game.h"
#include "GameUtils.h"
#include "GameAssets.h"
#include "EntitiesPool.h"

EntityPlayer::EntityPlayer() :
	m_Score(0),

	m_IsImmuneToDamage(false),
	m_Lives(3),
	
	m_Angle(0.0f),
	m_TurningRate(200.0f),

	m_IsThrust(false),
	m_ThrustSpeed(5.0f),

	m_FireTimerCurrent(0.0f),
	m_FireTimer(0.1f)
{
	m_Tag = GameData::PlayerTag;

	//if (m_Texture.loadFromFile("Assets/Ship.png"))
		//m_Sprite.setTexture(m_Texture);
	
	m_Texture = GameAssets::Get()->GetPlayerTexture();
	
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setColor(sf::Color::Blue);

	//m_BoundingRadius = m_Sprite.getGlobalBounds().getSize();

	Reset();
}

void EntityPlayer::Reset()
{
	auto rect = m_Sprite.getGlobalBounds();
	m_Sprite.setOrigin(rect.width * 0.5f, rect.height * 0.5f);

	m_Position = sf::Vector2f(Game::s_MainWindow->getSize().x * 0.5f, Game::s_MainWindow->getSize().y * 0.5f);
	m_Sprite.setPosition(m_Position);

	m_Velocity = sf::Vector2f(0.0f, 0.0f);

	m_FireTimerCurrent = m_FireTimer;
}

void EntityPlayer::Update(float DeltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)	|| sf::Keyboard::isKeyPressed(sf::Keyboard::A))	m_Angle -= m_TurningRate * DeltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) m_Angle += m_TurningRate * DeltaTime;
	
	m_IsThrust = (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W));
	if (m_IsThrust)
	{
		m_Velocity.x += std::sin(m_Angle * GameUtils::DEGTORAD) * 0.2f * DeltaTime;
		m_Velocity.y += -std::cos(m_Angle * GameUtils::DEGTORAD) * 0.2f * DeltaTime;
	}

	m_Position += m_Velocity;
	
	GameUtils::WrapCoordinates(m_Position.x, m_Position.y, m_Position.x, m_Position.y, (float)Game::s_MainWindow->getSize().x, (float)Game::s_MainWindow->getSize().y);

	m_Sprite.setRotation(m_Angle);
	m_Sprite.setPosition(m_Position);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_FireTimerCurrent += DeltaTime;
		if (m_FireTimerCurrent >= m_FireTimer)
		{
			EntityBullet* bullet = static_cast<EntityBullet*>(EntitiesPool::Get()->GetPooledEntity(EPT_Bullet));
			if (bullet)
			{
				bullet->SetActive(true);

				sf::Vector2f bulletVel = bullet->GetCurrentVelocity();
				bulletVel.x = std::sin(m_Angle * GameUtils::DEGTORAD) * 0.75f;
				bulletVel.y = -std::cos(m_Angle * GameUtils::DEGTORAD) * 0.75f;

				bullet->SetPosition(m_Sprite.getPosition());
				bullet->SetCurrentVelocity(bulletVel);

				m_FireTimerCurrent = 0.0f;
			}
		}
	}
	else
		m_FireTimerCurrent = m_FireTimer;
}

void EntityPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}

void EntityPlayer::OnCollision(Entity* OtherEntity)
{
	if (OtherEntity->GetTag() == GameData::AsteroidTag)
		ApplyDamage();
}

void EntityPlayer::ApplyDamage()
{
	if (m_Lives <= 0) return;

	m_Lives--;

	if (m_Lives <= 0)
		std::cout << "I am Dead!" << std::endl;
}