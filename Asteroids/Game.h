#pragma once
#include <SFML/Graphics.hpp>

class Entity;
class EntityPlayer;
class Game
{
public:
	Game(sf::RenderWindow& renderWindow);
	~Game();

	void Update(float DeltaTime);
	void Draw();

protected:
	sf::RenderWindow& m_MainWindow;

public:
	static sf::RenderWindow* s_MainWindow;

private:
	EntityPlayer* m_Player;
};