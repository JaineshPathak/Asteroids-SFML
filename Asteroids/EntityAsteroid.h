#pragma once
#include "Entity.h"

class EntityAsteroid : public Entity
{
	friend class Game;

public:
	EntityAsteroid();

	virtual void Reset() override;
	virtual void Update(float DeltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	const int GetType() const { return m_Type; }
	void SetType(const int& newType) { m_Type = newType; }

private:
	void OnDisable();

public:
	//Called when hit by bullet and based on Type
	void Split();

private:
	/* 1 - Small, 2 - Medium, 3 - Large */
	int m_Type;

	bool m_HasEnteredScreen;
};