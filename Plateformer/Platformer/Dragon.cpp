#include "Dragon.h"



Dragon::Dragon(sf::Vector2f position, sf::Texture &texture, float platformSize) : Ennemi(position, texture, platformSize)
{
	goingRight = true;
	speed = 1;
	currentSprite = 0;
	timer.restart();
	sprite.setOrigin(sf::Vector2f(48, 48));
	typeEnnemi = 0;
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
		sprite.scale(-1, 1);
	}
	else if (position.x >= bounds[1])
	{
		goingRight = false;
		sprite.scale(-1, 1);
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
	sprite.setTextureRect(sf::IntRect(currentSprite * 96, 0, 96, 96));
	window.draw(sprite);
	if (timer.getElapsedTime() >= sf::milliseconds(200) )
	{
		currentSprite++;
		timer.restart();
		if (currentSprite >= 3)
		{
			currentSprite = 0;
		}
	}
	
}

