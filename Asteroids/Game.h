#pragma once
#include <SFML/Graphics.hpp>
#include <vector>

class Entity;
class EntityPlayer;
class Game
{
public:
	Game(sf::RenderWindow& renderWindow);
	~Game();

	void Update(float DeltaTime);
	void Draw();

	template<typename T>
	T* SpawnEntity()
	{
		T* tE = new T();
		if(tE) m_EntitiesList.emplace_back(tE);

		return tE;
	}

protected:
	sf::RenderWindow& m_MainWindow;

public:
	static sf::RenderWindow* s_MainWindow;

private:
	std::vector<Entity*> m_EntitiesList;
	EntityPlayer* m_Player;
};