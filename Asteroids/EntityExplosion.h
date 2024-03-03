#pragma once
#include "Entity.h"

class EntityExplosion : public Entity
{
public:
	EntityExplosion();

	virtual void Reset() override;
	virtual void Update(float DeltaTime) override;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

	void PlayExplosion(const float& explosionScaleMultiplier = 1.0f);

private:
	bool m_IsPlaying;
	float m_ScaleTimeCurrent;
	float m_ScaleTime;
	float m_ScaleFactor;
	float m_ExplosionScaleMultiplier;

	sf::Color m_StartColour;
	sf::Color m_EndColour;
	sf::Color m_CurrentColour;
};