#pragma once
#include "Entity.h"

class EntityPlayer;
class EntityBullet : public Entity
{
public:
	EntityBullet();

	virtual void Reset() override;
	virtual void Update(float DeltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
	virtual void OnCollision(Entity* OtherEntity) override;
	virtual void SetOwner(Entity* newOwner) override;

private:
	EntityPlayer* m_EntityPlayerOwner;
};