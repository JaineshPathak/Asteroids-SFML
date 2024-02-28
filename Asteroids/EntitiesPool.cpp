#include "EntitiesPool.h"

#include "Game.h"
#include "Entity.h"
#include "EntityBullet.h"
#include "EntityAsteroid.h"

#include <iostream>

const int MAX_BULLETS = 100;
const int MAX_ASTEROIDS = 20;

EntitiesPool* EntitiesPool::s_Instance = nullptr;

EntitiesPool::EntitiesPool()
{
	s_Instance = this;

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		Entity* e = Game::SpawnEntity<EntityBullet>();
		e->SetActive(false);

		m_BulletsPool.push_back(e);
	}

	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		Entity* e = Game::SpawnEntity<EntityAsteroid>();
		e->SetActive(false);

		m_AsteroidsPool.push_back(e);
	}

	std::cout << "Entities Pool: Ready!" << std::endl;
}

EntitiesPool::~EntitiesPool()
{
	m_BulletsPool.clear();
	m_AsteroidsPool.clear();
}

Entity* EntitiesPool::GetPooledEntity(EntityPoolType entityType)
{
	auto start = (entityType == EPT_Bullet) ? m_BulletsPool.begin() : m_AsteroidsPool.begin();
	auto end = (entityType == EPT_Bullet) ? m_BulletsPool.end() : m_AsteroidsPool.end();
	for (auto i = start; i != end; i++)
	{
		if (!(*i)->IsActive())
			return (*i);
	}

	return nullptr;
}
