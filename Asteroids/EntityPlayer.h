#pragma once
#include "Entity.h"

class EntityPlayer : public Entity
{
public:
	EntityPlayer();

	virtual void Update(float DeltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void ApplyDamage();

protected:
	sf::Sprite m_Sprite;
	sf::Texture m_Texture;

private:
	int m_Score;

	bool m_IsImmuneToDamage;
	int m_Lives;

	float m_Angle;
	float m_TurningRate;
	
	bool m_IsThrust;
	float m_ThrustSpeed;
};