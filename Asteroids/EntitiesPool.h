#pragma once
#include <vector>

class Entity;
class EntityBullet;

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

	Entity* GetPooledEntity();

private:
	std::vector<Entity*> m_EntitesPool;

	static EntitiesPool* s_Instance;
};