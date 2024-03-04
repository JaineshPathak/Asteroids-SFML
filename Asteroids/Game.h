#pragma once
#include "PushdownState.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Entity;
class EntityPlayer;
class EntityAsteroid;
class EntityPowerup;
class EntitiesPool;
class GameUI;

class Game : public PushdownState
{
public:
	Game(sf::RenderWindow& renderWindow);
	~Game();

	static Game* Get() { return s_Instance; }

	virtual PushdownResult OnUpdate(float dt, PushdownState** newState) override;
	virtual void OnDraw() override;

	template<typename T>
	static T* SpawnEntity()
	{
		T* tE = new T();
		
		if (static_cast<Entity*>(tE) != nullptr)
			s_EntitiesList.push_back(tE);
		
		return tE;
	}

	EntityPlayer* GetPlayer() const { return m_EntityPlayer; }

	void OnAsteroidDestroyed(EntityAsteroid& enAsteroid);
	void OnPlayerScoreCentury();
	void OnPlayerDeath();

private:
	void SpawnAsteroid(bool shouldReset = false);

public:
	static sf::RenderWindow* s_MainWindow;

private:
	static Game* s_Instance;
	sf::RenderWindow& m_MainWindow;

	static std::vector<Entity*> s_EntitiesList;
	std::vector<Entity*> m_EntitiesActiveList;

	EntitiesPool* m_EntitiesPool;

	EntityPowerup* m_EntityPowerup;

	EntityPlayer* m_EntityPlayer;
	bool m_IsPlayerDead;
	float m_ReturnToTimer;
	float m_ReturnToTimerCurrent;

	GameUI* m_GameUI;
};