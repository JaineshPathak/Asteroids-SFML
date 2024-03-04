#include "EntityPlayer.h"

#include "Game.h"
#include "GameUtils.h"
#include "GameAssets.h"

#include "EntityAsteroid.h"
#include "EntityBullet.h"
#include "EntityExplosion.h"
#include "EntityPowerup.h"
#include "EntitiesPool.h"

EntityPlayer::EntityPlayer() :
	m_Score(0),
	m_Lives(3),

	m_Angle(0.0f),
	m_TurningRate(200.0f),

	m_IsThrust(false),
	m_ThrustSpeed(5.0f),

	m_FireTimerCurrent(0.0f),
	m_FireTimer(0.1f),

	m_IsImmuneToDamage(false),
	m_ImmuneTimerCurrent(0.0f),
	m_ImmuneTimer(3.0f),

	m_ImmuneTransparencyTimerCurrent(0.0),
	m_ImmuneTransparencyTimer(0.1f),

	m_IsOverPowered(false),
	m_OverPowerTimerCurrent(0.0f),
	m_OverPowerTimer(5.0f),

	m_DefaultColor(sf::Color::White)
{
	m_DefaultColor = sf::Color::Blue;

	m_Texture = GameAssets::Get()->GetPlayerTexture();
	
	m_Sprite.setTexture(m_Texture);
	m_Sprite.setColor(m_DefaultColor);

	Reset();
}

void EntityPlayer::Reset()
{
	if (!m_HasResetOrigin)
	{
		auto rect = m_Sprite.getGlobalBounds();
		m_Sprite.setOrigin(rect.width * 0.5f, rect.height * 0.5f);

		m_BoundingRadius = GameUtils::GetBoundingBoxRadius(rect.width, rect.height);
		m_HasResetOrigin = true;
	}

	m_Position = sf::Vector2f(Game::s_MainWindow->getSize().x * 0.5f, Game::s_MainWindow->getSize().y * 0.5f);
	m_Sprite.setPosition(m_Position);

	m_Velocity = sf::Vector2f(0.0f, 0.0f);

	m_FireTimerCurrent = m_FireTimer;
}

void EntityPlayer::Update(float DeltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)	|| sf::Keyboard::isKeyPressed(sf::Keyboard::A))	m_Angle -= m_TurningRate * DeltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) m_Angle += m_TurningRate * DeltaTime;
	
	if (m_Angle < 0.0f)		m_Angle += 360.0f;
	if (m_Angle > 360.0f)	m_Angle -= 360.0f;

	m_IsThrust = (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W));
	if (m_IsThrust)
	{
		m_Velocity.x += std::sin(m_Angle * GameUtils::DEGTORAD) * 0.45f * DeltaTime;
		m_Velocity.y += -std::cos(m_Angle * GameUtils::DEGTORAD) * 0.45f * DeltaTime;
	}

	m_Position += m_Velocity;
	
	GameUtils::WrapCoordinates(m_Position.x, m_Position.y, m_Position.x, m_Position.y, (float)Game::s_MainWindow->getSize().x, (float)Game::s_MainWindow->getSize().y, m_BoundingRadius);

	m_Sprite.setRotation(m_Angle);
	m_Sprite.setPosition(m_Position);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_IsOverPowered)
	{
		m_FireTimerCurrent += DeltaTime;
		if (m_FireTimerCurrent >= m_FireTimer)
		{
			SpawnBullet();
			m_FireTimerCurrent = 0.0f;
		}
	}
	else if (m_IsOverPowered)
	{
		m_FireTimerCurrent += DeltaTime;
		if (m_FireTimerCurrent >= (m_FireTimer * 2.5f))
		{
			m_FireTimerCurrent = 0.0f;
			for (int i = 0; i < 6; i++)
			{
				float angle = 2.0f * 3.14f * (float)i / 6.0f;
				angle += (m_Angle * GameUtils::DEGTORAD) * 3.14f;

				sf::Vector2f bulletAtAngleVel;
				bulletAtAngleVel.x = std::sinf(angle) * 1.5f;
				bulletAtAngleVel.y = -std::cosf(angle) * 1.5f;

				SpawnBullet(bulletAtAngleVel, true);
			}
		}
	}
	else
		m_FireTimerCurrent = m_FireTimer;

	if (m_IsImmuneToDamage)
	{
		m_ImmuneTimerCurrent += DeltaTime;
		const float tolerance = 0.01f;
		
		m_ImmuneTransparencyTimerCurrent += DeltaTime;
		if (m_ImmuneTransparencyTimerCurrent >= m_ImmuneTransparencyTimer)
		{
			sf::Color playerColor = m_Sprite.getColor();
			playerColor.a ^= 255;
			m_Sprite.setColor(playerColor);

			m_ImmuneTransparencyTimerCurrent = 0.0f;
		}

		if (m_ImmuneTimerCurrent >= m_ImmuneTimer)
		{
			m_IsImmuneToDamage = false;
			m_ImmuneTimerCurrent = 0.0f;
			m_ImmuneTransparencyTimerCurrent = 0.0f;

			m_Sprite.setColor(m_DefaultColor);
		}
	}

	if (m_IsOverPowered)
	{
		m_OverPowerTimerCurrent += DeltaTime;
		if (m_OverPowerTimerCurrent >= m_OverPowerTimer)
		{
			m_IsOverPowered = false;
			m_OverPowerTimerCurrent = 0.0f;
		}
	}
}

void EntityPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}

void EntityPlayer::OnCollision(Entity* OtherEntity)
{
	//Is it an Asteroid?
	EntityAsteroid* rock = dynamic_cast<EntityAsteroid*>(OtherEntity);
	if (rock && !m_IsImmuneToDamage && !m_IsOverPowered)
		ApplyDamage();

	//Is it a Powerup?
	EntityPowerup* powerup = dynamic_cast<EntityPowerup*>(OtherEntity);
	if (powerup)
	{
		m_IsOverPowered = true;
		m_OverPowerTimerCurrent = 0.0f;

		powerup->SetActive(false);
	}
}

void EntityPlayer::AddScore(const int& scoreAmount)
{
	m_Score += scoreAmount;

	if ((m_Score % 50) == 0)
		Game::Get()->OnPlayerScoreCentury();
}

void EntityPlayer::ApplyDamage()
{
	if (m_Lives <= 0) return;

	m_Lives--;
	if (m_Lives <= 0)
	{
		//Spawn an Explosion
		EntityExplosion* explosion = static_cast<EntityExplosion*>(EntitiesPool::Get()->GetPooledEntity(EPT_Explosion));
		if (explosion)
		{
			explosion->SetActive(true);
			explosion->Reset();
			explosion->SetPosition(m_Sprite.getPosition());
			explosion->PlayExplosion(2.0f);
		}

		Game::Get()->OnPlayerDeath();
		return;
	}

	m_ImmuneTimerCurrent = 0.0f;
	m_IsImmuneToDamage = true;
	
	Reset();
}

void EntityPlayer::SpawnBullet(const sf::Vector2f& newBulletVel, const bool& velocityOverride)
{
	EntityBullet* bullet = static_cast<EntityBullet*>(EntitiesPool::Get()->GetPooledEntity(EPT_Bullet));
	if (bullet)
	{
		bullet->SetActive(true);

		if (!velocityOverride)
		{
			sf::Vector2f bulletVel = bullet->GetVelocity();
			bulletVel.x = std::sinf(m_Angle * GameUtils::DEGTORAD) * 1.15f;
			bulletVel.y = -std::cosf(m_Angle * GameUtils::DEGTORAD) * 1.15f;

			bullet->SetVelocity(bulletVel);
		}
		else
			bullet->SetVelocity(newBulletVel);

		bullet->SetPosition(m_Sprite.getPosition());
	}
}
