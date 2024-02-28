#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable, public sf::Transformable
{
public:
	virtual ~Entity() {};

	virtual void Reset() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	
	virtual void OnCollision(Entity* OtherEntity) = 0;

	const bool IsActive() const { return m_Active; }
	void SetActive(const bool& status) { m_Active = status; }

	const std::string GetTag() const { return m_Tag; }

	void SetPosition(const sf::Vector2f& newPos) { m_Position = newPos; }

	void SetCurrentVelocity(const sf::Vector2f& newVelocity) { m_Velocity = newVelocity; }
	const sf::Vector2f GetCurrentVelocity() const { return m_Velocity; }

	const sf::Sprite GetSprite() const { return m_Sprite; }

protected:
	bool m_Active = true;
	float m_BoundingRadius;

	std::string m_Tag = "Entity";

	sf::Vector2f m_Velocity;
	sf::Vector2f m_Position;

	sf::Sprite m_Sprite;
	sf::Texture m_Texture;
};