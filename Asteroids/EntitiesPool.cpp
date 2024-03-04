#include "EntitiesPool.h"

#include "Game.h"
#include "Entity.h"
#include "EntityBullet.h"
#include "EntityAsteroid.h"
#include "EntityExplosion.h"

#include <iostream>

const int MAX_BULLETS = 150;
const int MAX_ASTEROIDS = 20;
const int MAX_EXPLOSIONS = 20;

EntitiesPool* EntitiesPool::s_Instance = nullptr;

EntitiesPool::EntitiesPool()
{
	s_Instance = this;

	for (int i = 0; i < MAX_BULLETS; i++)
	{
		Entity* e = Game::SpawnEntity<EntityBullet>();
		e->SetActive(false);
		e->SetOwner((Entity*)(Game::Get()->GetPlayer()));

		m_BulletsPool.push_back(e);
	}

	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		Entity* e = Game::SpawnEntity<EntityAsteroid>();
		e->SetActive(false);

		m_AsteroidsPool.push_back(e);
	}

	for (int i = 0; i < MAX_ASTEROIDS; i++)
	{
		Entity* e = Game::SpawnEntity<EntityExplosion>();
		e->SetActive(false);

		m_ExplosionsPool.push_back(e);
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
	std::vector<Entity*>::iterator start;
	std::vector<Entity*>::iterator end;
	
	switch (entityType)
	{
	case EPT_Bullet:	{ start = m_BulletsPool.begin(); end = m_BulletsPool.end(); break; }
	case EPT_Asteroid:	{ start = m_AsteroidsPool.begin(); end = m_AsteroidsPool.end(); break; }
	case EPT_Explosion: { start = m_ExplosionsPool.begin(); end = m_ExplosionsPool.end(); break; }
	}

	for (auto& i = start; i != end; i++)
	{
		if (!(*i)->IsActive())
			return (*i);
	}

	return nullptr;
}
