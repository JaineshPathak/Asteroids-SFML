#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

class Entity;
class EntityPlayer;
class EntityAsteroid;
class EntitiesPool;
class GameUI;

class Game
{
public:
	Game(sf::RenderWindow& renderWindow);
	~Game();

	static Game* Get() { return s_Instance; }

	void Update(float DeltaTime);
	void Draw();

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

	EntityPlayer* m_EntityPlayer;
	EntitiesPool* m_EntitiesPool;

	GameUI* m_GameUI;
};