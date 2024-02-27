#include <iostream>

#include "Game.h"
#include "EntityPlayer.h"

sf::RenderWindow* Game::s_MainWindow = nullptr;

Game::Game(sf::RenderWindow& renderWindow) : 
	m_MainWindow(renderWindow),
	m_Player(nullptr)
{
	s_MainWindow = &m_MainWindow;

	//m_Player = new EntityPlayer();
	//m_EntitiesList.emplace_back(m_Player);

	m_Player = SpawnEntity<EntityPlayer>();
}

Game::~Game()
{
	s_MainWindow = nullptr;
	
	for (auto i : m_EntitiesList)
		delete i;

	m_Player = nullptr;
}

void Game::Update(float DeltaTime)
{
	//m_Player->Update(DeltaTime);
	for (auto i : m_EntitiesList)
	{
		if (!i->IsActive()) continue;

		i->Update(DeltaTime);
	}
}

void Game::Draw()
{
	for (auto i : m_EntitiesList)
	{
		if (!i->IsActive()) continue;

		m_MainWindow.draw(*i);
	}
}