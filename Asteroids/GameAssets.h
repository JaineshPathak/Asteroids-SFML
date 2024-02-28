#pragma once
#include <SFML/Graphics.hpp>

class GameAssets
{
public:
	GameAssets();
	~GameAssets();

	static GameAssets* Get()
	{
		if (s_Instance == nullptr)
			s_Instance = new GameAssets();

		return s_Instance;
	}

	inline const sf::Texture GetPlayerTexture() { return m_PlayerTexture; }
	inline const sf::Texture GetAsteroidTexture() { return m_AsteroidTexture; }

private:
	sf::Texture m_PlayerTexture;
	sf::Texture m_AsteroidTexture;

	static GameAssets* s_Instance;
};