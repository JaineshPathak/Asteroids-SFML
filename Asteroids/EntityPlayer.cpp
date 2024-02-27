#include <iostream>

#include "EntityPlayer.h"
#include "Game.h"
#include "GameUtils.h"

EntityPlayer::EntityPlayer() :
	m_Score(0),

	m_IsImmuneToDamage(false),
	m_Lives(3),
	
	m_Angle(0.0f),
	m_TurningRate(200.0f),

	m_IsThrust(false),
	m_ThrustSpeed(5.0f)
{
	m_Tag = "Player";

	if (m_Texture.loadFromFile("Assets/Ship.png"))
		m_Sprite.setTexture(m_Texture);

	auto rect = m_Sprite.getGlobalBounds();
	m_Sprite.setOrigin(rect.width * 0.5f, rect.height * 0.5f);

	//Place this at Center of Screen
	m_Position = sf::Vector2f(Game::s_MainWindow->getSize().x * 0.5f, Game::s_MainWindow->getSize().y * 0.5f);
	m_Sprite.setPosition(m_Position);
}

void EntityPlayer::Update(float DeltaTime)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)	|| sf::Keyboard::isKeyPressed(sf::Keyboard::A))	m_Angle -= m_TurningRate * DeltaTime;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) m_Angle += m_TurningRate * DeltaTime;
	
	m_IsThrust = (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W));
	if (m_IsThrust)
	{
		m_Velocity.x += std::sin(m_Angle * DEGTORAD) * 0.2f * DeltaTime;
		m_Velocity.y += -std::cos(m_Angle * DEGTORAD) * 0.2f * DeltaTime;
	}

	m_Position += m_Velocity;
	
	WrapCoordinates(m_Position.x, m_Position.y, m_Position.x, m_Position.y, (float)Game::s_MainWindow->getSize().x, (float)Game::s_MainWindow->getSize().y);

	m_Sprite.setRotation(m_Angle);
	m_Sprite.setPosition(m_Position);
}

void EntityPlayer::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(m_Sprite);
}

void EntityPlayer::ApplyDamage()
{
	if (m_Lives <= 0) return;

	m_Lives--;
}