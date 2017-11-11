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
	virtual void Draw(sf::RenderWindow &window) = 0;
	float GetWidth();
	float GetHeight();
	int GetEnnemiType(); // 0 pour dragon 1 pour chevalier 2 pour slime
	Ennemi();

protected:
	sf::Vector2f position;
	sf::Sprite sprite;
	float bounds[2]; // bounds[0] est la première limite en x, bounds[1] est la deuxième limite en x
	bool goingRight;
	sf::Clock timer;
	sf::Texture texture;
	int typeEnnemi;
};

