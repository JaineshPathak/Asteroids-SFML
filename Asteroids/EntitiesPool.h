#pragma once
#include <vector>

class Entity;
class EntityBullet;

enum EntityPoolType
{
	EPT_Bullet,
	EPT_Asteroid
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

	static EntitiesPool* s_Instance;
};