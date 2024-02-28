#include <iostream>

#include "Game.h"
#include "GameUtils.h"
#include "EntityPlayer.h"
#include "EntityAsteroid.h"
#include "EntitiesPool.h"

sf::RenderWindow* Game::s_MainWindow = nullptr;
std::vector<Entity*> Game::s_EntitiesList;

const std::string GameData::PlayerTag = "Player";
const std::string GameData::BulletTag = "Bullet";
const std::string GameData::AsteroidTag = "Asteroid";

Game::Game(sf::RenderWindow& renderWindow) : 
	m_MainWindow(renderWindow)
{
	s_MainWindow = &m_MainWindow;

	Game::SpawnEntity<EntityPlayer>();
	
	m_EntitiesPool = new EntitiesPool();

	//Spawn a Random Asteroid
	for (int i = 0; i < 5; i++)
	{
		EntityAsteroid* Rock = static_cast<EntityAsteroid*>(m_EntitiesPool->GetPooledEntity(EPT_Asteroid));
		if (Rock)
		{
			Rock->SetActive(true);

			sf::Vector2f newPos;
			newPos.x = GameUtils::RandF(0.0f, (float)m_MainWindow.getSize().x);
			newPos.y = GameUtils::RandF(0.0f, (float)m_MainWindow.getSize().y);

			sf::Vector2f newVel;
			newVel.x = GameUtils::RandF(-0.1f, 0.1f);
			newVel.y = GameUtils::RandF(-0.1f, 0.1f);
		
			Rock->SetPosition(newPos);
			Rock->SetCurrentVelocity(newVel);
		}
	}
}

Game::~Game()
{
	s_MainWindow = nullptr;
	
	delete m_EntitiesPool;
	m_EntitiesPool = nullptr;

	for (auto i : s_EntitiesList)
		delete i;

	m_EntitiesActiveList.clear();
}

void Game::Update(float DeltaTime)
{
	m_EntitiesActiveList.clear();

	//Populate list of active entities
	for (auto it = s_EntitiesList.begin(); it != s_EntitiesList.end(); ++it)
	{
		Entity* e = *it;

		if (e->IsActive())
			m_EntitiesActiveList.push_back(e);
	}

	//Update entities that are Active
	for (auto& e : m_EntitiesActiveList)
		e->Update(DeltaTime);

	//Check for Collisions
	for (auto& eA : m_EntitiesActiveList)
	{
		for (auto& eB : m_EntitiesActiveList)
		{
			if (eA != eB && eA->GetSprite().getGlobalBounds().intersects(eB->GetSprite().getGlobalBounds()))
			{
				//std::cout << "Collision of A: " << eA->GetTag() << " with B: " << eB->GetTag() << std::endl;
				eA->OnCollision(eB);
				eB->OnCollision(eA);
			}
		}
	}
}

void Game::Draw()
{
	//Only Draw Active Entities
	for (auto& i : m_EntitiesActiveList)
		m_MainWindow.draw(*i);
}