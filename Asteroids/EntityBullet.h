#pragma once
#include "Entity.h"

class EntityBullet : public Entity
{
public:
	EntityBullet();

	virtual void Reset() override;
	virtual void Update(float DeltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void OnCollision(Entity* OtherEntity) override;

protected:
	sf::Sprite m_Sprite;
	sf::Texture m_Texture;
};