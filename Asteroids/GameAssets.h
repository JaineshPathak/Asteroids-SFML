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

	inline const sf::Texture GetPlayerTexture() const { return m_PlayerTexture; }
	inline const sf::Texture GetAsteroidTexture() const { return m_AsteroidTexture; }

	inline const sf::Font GetGameFont() const { return m_GameFont; }

private:
	sf::Texture m_PlayerTexture;
	sf::Texture m_AsteroidTexture;

	sf::Font m_GameFont;

	static GameAssets* s_Instance;
};