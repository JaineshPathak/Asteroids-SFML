#include <iostream>

#include "Game.h"
#include "EntityPlayer.h"

sf::RenderWindow* Game::s_MainWindow = nullptr;

Game::Game(sf::RenderWindow& renderWindow) : 
	m_MainWindow(renderWindow),
	m_Player(nullptr)
{
	s_MainWindow = &m_MainWindow;

	m_Player = new EntityPlayer();
}

Game::~Game()
{
	s_MainWindow = nullptr;

	delete m_Player;
}

void Game::Update(float DeltaTime)
{
	m_Player->Update(DeltaTime);
}

void Game::Draw()
{
	m_MainWindow.draw(*m_Player);
}