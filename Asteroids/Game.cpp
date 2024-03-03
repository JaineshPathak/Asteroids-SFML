#include <iostream>

#include "Game.h"
#include "GameIntroUI.h"
#include "GamePauseUI.h"
#include "GameUI.h"
#include "GameUtils.h"

#include "EntityPlayer.h"
#include "EntityAsteroid.h"
#include "EntitiesPool.h"


Game* Game::s_Instance = nullptr;
sf::RenderWindow* Game::s_MainWindow = nullptr;
std::vector<Entity*> Game::s_EntitiesList;

Game::Game(sf::RenderWindow& renderWindow) : 
	m_MainWindow(renderWindow),
	m_IsPlayerDead(false),
	m_ReturnToTimer(2.0f),
	m_ReturnToTimerCurrent(0.0f)
{
	s_Instance = this;
	s_MainWindow = &m_MainWindow;

	//Create Player
	m_EntityPlayer = Game::SpawnEntity<EntityPlayer>();

	//Create UI
	m_GameUI = new GameUI(m_MainWindow, *m_EntityPlayer);
	
	//Create Pool of Entities like Bullets/Asteroids
	m_EntitiesPool = new EntitiesPool();

	//Spawn 5 Random Asteroids
	for (int i = 0; i < 5; i++)
		SpawnAsteroid();

	std::cout << "Game: Ready!" << std::endl;
}

Game::~Game()
{
	s_MainWindow = nullptr;
	
	delete m_EntitiesPool;
	m_EntitiesPool = nullptr;

	for (auto i : s_EntitiesList)
	{
		delete i;
		i = nullptr;
	}

	m_EntityPlayer = nullptr;

	s_EntitiesList.clear();
	m_EntitiesActiveList.clear();

	delete m_GameUI;
	m_GameUI = nullptr;
}

/*void Game::Update(float DeltaTime)
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
				//dddeB->OnCollision(eA);
			}
		}
	}

	m_GameUI->Update();
}*/

/*void Game::Draw()
{
	//Only Draw Active Entities
	for (auto& i : m_EntitiesActiveList)
		m_MainWindow.draw(*i);

	m_GameUI->Draw();
}*/

PushdownState::PushdownResult Game::OnUpdate(float DeltaTime, PushdownState** newState)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape) && !m_IsPlayerDead)
	{
		*newState = new GamePauseUI(m_MainWindow, *m_EntityPlayer);
		return PushdownResult::PR_Push;
	}

	if (m_IsPlayerDead)
	{
		m_ReturnToTimerCurrent += DeltaTime;
		if (m_ReturnToTimerCurrent >= m_ReturnToTimer)
		{
			m_ReturnToTimerCurrent = 0.0f;

			*newState = new GameIntroUI(m_MainWindow);
			return PushdownResult::PR_Pop;
		}
	}

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
				//dddeB->OnCollision(eA);
			}
		}
	}

	m_GameUI->Update();

	return PushdownResult::PR_NoChange;
}

void Game::OnDraw()
{
	//Only Draw Active Entities
	for (auto& i : m_EntitiesActiveList)
		m_MainWindow.draw(*i);

	m_GameUI->Draw();
}

//Called when a small Asteroid is destroyed. So resets its type to random type and start spawning new Asteroids 
void Game::OnAsteroidDestroyed(EntityAsteroid& enAsteroid)
{
	enAsteroid.SetType(GameUtils::RandI(1, 4));

	SpawnAsteroid(true);
}

void Game::OnPlayerDeath()
{
	m_ReturnToTimerCurrent = 0.0f;

	m_IsPlayerDead = true;
	m_EntityPlayer->SetActive(false);
}

void Game::SpawnAsteroid(bool shouldReset)
{
	EntityAsteroid* Rock = static_cast<EntityAsteroid*>(m_EntitiesPool->GetPooledEntity(EPT_Asteroid));
	if (Rock)
	{
		Rock->SetActive(true);

		if (shouldReset) Rock->Reset();

		//Set the position of random outside screen
		sf::Vector2f newPos;
		GameUtils::SetPosRandomOutsideScreen(newPos.x, newPos.y, (float)m_MainWindow.getSize().x, (float)m_MainWindow.getSize().y);

		//Get random in-screen Position
		sf::Vector2f randScreenPos;
		GameUtils::GetPosRandomInsideScreen(randScreenPos.x, randScreenPos.y, (float)m_MainWindow.getSize().x, (float)m_MainWindow.getSize().y);

		//Get the Direction from Asteroid off-Screen Position to random in-Screen Position
		sf::Vector2f newVel;
		newVel.x = randScreenPos.x - newPos.x;
		newVel.y = randScreenPos.y - newPos.y;

		//Normalise the Direction
		float len = sqrt((newVel.x * newVel.x) + (newVel.y * newVel.y));
		newVel.x /= len;
		newVel.y /= len;

		Rock->SetPosition(newPos);
		Rock->SetCurrentVelocity(newVel * 0.1f);
	}
}