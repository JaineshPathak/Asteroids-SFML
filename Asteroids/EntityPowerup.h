#pragma once
#include "Entity.h"

class EntityPowerup : public Entity
{
public:
	EntityPowerup();

	virtual void Reset() override;
	virtual void Update(float DeltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
	float m_ElaspedTime;
	float m_ScaleFrequency;
	float m_ScaleFactor;

	sf::Color m_Color1;
	sf::Color m_Color2;
	sf::Color m_CurrentColor;
	float m_ColorFactor;
};