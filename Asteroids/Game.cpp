#include <iostream>

#include "Game.h"
#include "EntityPlayer.h"
#include "EntitiesPool.h"

sf::RenderWindow* Game::s_MainWindow = nullptr;
std::vector<Entity*> Game::s_EntitiesList;

Game::Game(sf::RenderWindow& renderWindow) : 
	m_MainWindow(renderWindow)
{
	s_MainWindow = &m_MainWindow;

	//m_Player = new EntityPlayer();
	//m_EntitiesList.emplace_back(m_Player);

	Game::SpawnEntity<EntityPlayer>();
	
	m_EntitiesPool = new EntitiesPool();
	//m_EntitiesList.emplace_back(m_Player);
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
	for (auto it = s_EntitiesList.begin(); it != s_EntitiesList.end(); ++it)
	{
		Entity* e = *it;

		if (e->IsActive())
			m_EntitiesActiveList.push_back(e);
	}

	// Update entities that need updates
	for (auto& e : m_EntitiesActiveList)
		e->Update(DeltaTime);
}

void Game::Draw()
{
	//Only Draw Active Entities
	for (auto& i : m_EntitiesActiveList)
		m_MainWindow.draw(*i);
}