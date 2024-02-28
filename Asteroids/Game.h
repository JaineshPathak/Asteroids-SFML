#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>

struct GameData
{
	static const std::string PlayerTag;
	static const std::string BulletTag;
	static const std::string AsteroidTag;
};

class Entity;
class EntityPlayer;
class EntitiesPool;
class Game
{
public:
	Game(sf::RenderWindow& renderWindow);
	~Game();

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

protected:
	sf::RenderWindow& m_MainWindow;

public:
	static sf::RenderWindow* s_MainWindow;

private:
	static std::vector<Entity*> s_EntitiesList;

	std::vector<Entity*> m_EntitiesActiveList;
	EntitiesPool* m_EntitiesPool;
};