#include "EntitiesPool.h"

#include "Game.h"
#include "Entity.h"
#include "EntityBullet.h"

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

		m_EntitesPool.push_back(e);
	}

	std::cout << "Entities Pool: Ready!" << std::endl;
}

EntitiesPool::~EntitiesPool()
{
	m_EntitesPool.clear();
}

Entity* EntitiesPool::GetPooledEntity()
{
	for (auto i = m_EntitesPool.begin(); i != m_EntitesPool.end(); i++)
	{
		if (!(*i)->IsActive())
			return (*i);
	}

	return nullptr;
}
