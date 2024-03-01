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

	const int GetLivesCount() const { return m_Lives; }

	const int GetScoreCount() const { return m_Score; }
	void AddScore(const int& scoreAmount) { m_Score += scoreAmount; }

	void ApplyDamage();

private:
	int m_Score;
	int m_Lives;

	float m_Angle;
	float m_TurningRate;
	
	bool m_IsThrust;
	float m_ThrustSpeed;

	float m_FireTimerCurrent;
	float m_FireTimer;

	bool m_IsImmuneToDamage;
	float m_ImmuneTimerCurrent;
	float m_ImmuneTimer;

	float m_ImmuneTransparencyTimerCurrent;
	float m_ImmuneTransparencyTimer;

	sf::Color m_DefaultColor;
};