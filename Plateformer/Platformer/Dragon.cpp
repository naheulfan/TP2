#include "Dragon.h"



Dragon::Dragon(sf::Vector2f position, sf::Texture &texture, float platformSize) : Ennemi(position, texture, platformSize)
{
	goingRight = true;
	speed = 1;
}
Dragon::Dragon()
{
}

Dragon::~Dragon()
{
}
void Dragon::Update()
{
	if (position.x <= bounds[0])
	{
		goingRight = true;
	}
	else if (position.x >= bounds[1])
	{
		goingRight = false;
	}
	if (goingRight)
	{
		position.x += speed;
	}
	else
	{
		position.x -= speed;
	}
	position.y += 1;
}

