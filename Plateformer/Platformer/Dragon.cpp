#include "Dragon.h"



Dragon::Dragon(sf::Vector2f position, sf::Texture &texture, float platformSize) : Ennemi(position, texture, platformSize)
{
	goingRight = true;
	speed = 1;
	currentSprite = 0;
	timer.restart();
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
void Dragon::Draw(sf::RenderWindow &window)
{
	sprite.setPosition(position);
	sprite.setTextureRect(sf::IntRect(currentSprite + 2 * 64, currentSprite + 2 * 64, 64, 64));
	window.draw(sprite);
	currentSprite++;
	if (timer.getElapsedTime() >= sf::milliseconds(2000) )
	{
		//currentSprite++;
		timer.restart();
		if (currentSprite > 9)
		{
			currentSprite = 0;
		}
	}
	
}

