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
	void AddScore(const int& scoreAmount);

	void ApplyDamage();

private:
	void SpawnBullet(const sf::Vector2f& newBulletVel = sf::Vector2f(0.0f, 0.0f), const bool& velocityOverride = false);

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

	bool m_IsOverPowered;
	float m_OverPowerTimerCurrent;
	float m_OverPowerTimer;

	sf::Color m_DefaultColor;
};