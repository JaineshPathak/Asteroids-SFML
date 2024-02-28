#pragma once
#include "Entity.h"

class EntityAsteroid : public Entity
{
public:
	EntityAsteroid();

	virtual void Reset() override;
	virtual void Update(float DeltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void OnCollision(Entity* OtherEntity) override;

	//Called when hit by bullet and based on Type
	void Split();

private:
	int m_Type;
};