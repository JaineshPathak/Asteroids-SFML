#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable, public sf::Transformable
{
public:
	virtual void Update(float DeltaTime) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	std::string GetTag() const { return m_Tag; }
	sf::Vector2f GetCurrentVelocity() const { return m_Velocity; }

protected:
	std::string m_Tag = "Entity";

	sf::Vector2f m_Velocity;
	sf::Vector2f m_Position;
};