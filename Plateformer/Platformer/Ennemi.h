#pragma once
#include <SFML\Graphics.hpp>
class Ennemi
{
public:
	Ennemi(sf::Vector2f basePos, sf::Texture &texture);
	~Ennemi();
	sf::Vector2f Getposition();
	void SetPosition(sf::Vector2f newPos);
	virtual void Update() =0;
	void Draw(sf::RenderWindow &window);

protected:
	sf::Vector2f position;
	sf::Sprite sprite;
};

