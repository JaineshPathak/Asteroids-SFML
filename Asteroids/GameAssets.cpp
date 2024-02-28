#include "GameAssets.h"
#include <iostream>

GameAssets* GameAssets::s_Instance = nullptr;

const std::string AssetShipPath("Assets/Ship.png");
const std::string AssetAsteroidPath("Assets/Asteroid.png");

GameAssets::GameAssets()
{
	s_Instance = this;

	if (m_PlayerTexture.loadFromFile(AssetShipPath))
	{
		m_PlayerTexture.setSmooth(true);
		std::cout << "Game Asset: Loaded Texture: " << AssetShipPath << std::endl;
	}

	if (m_AsteroidTexture.loadFromFile("Assets/Asteroid.png"))
	{
		m_AsteroidTexture.setSmooth(true);
		std::cout << "Game Asset: Loaded Texture: " << AssetAsteroidPath << std::endl;
	}
}

GameAssets::~GameAssets()
{
	delete s_Instance;
	s_Instance = nullptr;
}
