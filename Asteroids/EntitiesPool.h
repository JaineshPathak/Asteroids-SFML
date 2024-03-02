#pragma once
#include <vector>

class Entity;

enum EntityPoolType
{
	EPT_Bullet,
	EPT_Asteroid,
	EPT_Explosion
};

class EntitiesPool
{
public:
	EntitiesPool();
	~EntitiesPool();

	static EntitiesPool* Get()
	{
		if (s_Instance == nullptr)
			s_Instance = new EntitiesPool();

		return s_Instance;
	}

	Entity* GetPooledEntity(EntityPoolType entityType);

private:
	std::vector<Entity*> m_BulletsPool;
	std::vector<Entity*> m_AsteroidsPool;
	std::vector<Entity*> m_ExplosionsPool;

	static EntitiesPool* s_Instance;
};