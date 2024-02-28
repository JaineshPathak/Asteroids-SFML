#pragma once
#include "Entity.h"

class EntityPlayer : public Entity
{
public:
	EntityPlayer();

	virtual void Reset() override;
	virtual void Update(float DeltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	virtual void OnCollision(Entity* OtherEntity) override;

	void ApplyDamage();

private:
	int m_Score;

	bool m_IsImmuneToDamage;
	int m_Lives;

	float m_Angle;
	float m_TurningRate;
	
	bool m_IsThrust;
	float m_ThrustSpeed;

	float m_FireTimerCurrent;
	float m_FireTimer;
};