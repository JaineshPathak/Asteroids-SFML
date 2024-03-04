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

	inline sf::Texture GetPlayerTexture() const { return m_PlayerTexture; }
	inline sf::Texture GetAsteroidTexture() const { return m_AsteroidTexture; }

	inline sf::Font GetGameFont() const { return m_GameFont; }

private:
	sf::Texture m_PlayerTexture;
	sf::Texture m_AsteroidTexture;

	sf::Font m_GameFont;

	static GameAssets* s_Instance;
};