#pragma once
#include "Ennemi.h"
class Slime : public Ennemi
{
public:
	Slime::Slime();
	Slime(sf::Vector2f position, sf::Texture &texture, float platformSize);
	~Slime();
	void Update();
	void Draw(sf::RenderWindow &window);

private:
	float speed;
	int currentSprite;
};

