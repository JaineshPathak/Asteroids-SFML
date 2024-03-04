#pragma once
#include <SFML/Graphics.hpp>

class Entity : public sf::Drawable
{
public:
	virtual ~Entity() {};

	virtual void Reset() = 0;
	virtual void Update(float DeltaTime) = 0;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
	
	virtual void OnCollision(Entity* OtherEntity) {};

	const bool IsActive() const { return m_Active; }
	void SetActive(const bool& status) { m_Active = status; }

	Entity* GetOwner() const { return m_EntityOwner; }
	virtual void SetOwner(Entity* newOwner) { m_EntityOwner = newOwner; }

	void SetPosition(const sf::Vector2f& newPos) { m_Position = newPos; }

	void SetVelocity(const sf::Vector2f& newVelocity) { m_Velocity = newVelocity; }
	const sf::Vector2f GetVelocity() const { return m_Velocity; }

	const sf::Sprite GetSprite() const { return m_Sprite; }
	const sf::Texture GetTexture() const { return m_Texture; }

protected:
	bool m_HasResetOrigin = false;

	bool m_Active = true;
	float m_BoundingRadius = 0.0f;

	Entity* m_EntityOwner;

	sf::Vector2f m_Velocity;
	sf::Vector2f m_Position;

	sf::Sprite m_Sprite;
	sf::Texture m_Texture;
};