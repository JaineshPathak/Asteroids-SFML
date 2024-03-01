#include "GameAssets.h"
#include <iostream>

GameAssets* GameAssets::s_Instance = nullptr;

const std::string AssetShipPath("Assets/Ship.png");
const std::string AssetAsteroidPath("Assets/Asteroid.png");
const std::string AssetFontPath("Assets/1StSortie-4nVY.ttf");

GameAssets::GameAssets()
{
	s_Instance = this;

	if (m_PlayerTexture.loadFromFile(AssetShipPath))
	{
		m_PlayerTexture.setSmooth(true);
		std::cout << "Game Asset: Loaded Texture: " << AssetShipPath << std::endl;
	}

	if (m_AsteroidTexture.loadFromFile(AssetAsteroidPath))
	{
		m_AsteroidTexture.setSmooth(true);
		std::cout << "Game Asset: Loaded Texture: " << AssetAsteroidPath << std::endl;
	}

	if (m_GameFont.loadFromFile(AssetFontPath))
	{
		m_GameFont.setSmooth(true);
		std::cout << "Game Asset: Loaded Font: " << AssetFontPath << std::endl;
	}
}

GameAssets::~GameAssets()
{
	std::cout << "Game Asset: Destroyed" << std::endl;

	delete s_Instance;
	s_Instance = nullptr;
}
