#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable, public sf::Transformable
{
public:
	virtual void Update(float DeltaTime) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	const bool IsActive() const { return m_Active; }
	void SetActive(const bool& status) { m_Active = status; }

	const std::string GetTag() const { return m_Tag; }
	const sf::Vector2f GetCurrentVelocity() const { return m_Velocity; }

protected:
	bool m_Active = true;

	std::string m_Tag = "Entity";

	sf::Vector2f m_Velocity;
	sf::Vector2f m_Position;
};