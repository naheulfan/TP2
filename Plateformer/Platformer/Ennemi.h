#pragma once
#include <SFML\Graphics.hpp>
class Ennemi
{
public:
	Ennemi(sf::Vector2f basePos, sf::Texture &texture, float platformSize);
	~Ennemi();
	sf::Vector2f Getposition();
	void SetPosition(sf::Vector2f newPos);
	virtual void Update() =0;
	void Draw(sf::RenderWindow &window);
	Ennemi();

protected:
	sf::Vector2f position;
	sf::Sprite sprite;
	float bounds[2]; // bounds[0] est la première limite en x, bounds[1] est la deuxième limite en x
};

