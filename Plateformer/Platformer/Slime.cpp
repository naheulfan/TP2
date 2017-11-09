#include "Slime.h"



Slime::Slime(sf::Vector2f position, sf::Texture &texture, float platformSize) : Ennemi(position, texture, platformSize)
{
	goingRight = true;
	speed = 1;
	currentSprite = 0;
	timer.restart();
	sprite.setOrigin(sf::Vector2f(16, 10));
}
Slime::Slime()
{
}

Slime::~Slime()
{
}
void Slime::Update()
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
void Slime::Draw(sf::RenderWindow &window)
{
	sprite.setPosition(position);
	int spriteDecider = 0;
	if (currentSprite == 3)
	{
		spriteDecider = 1;
	}
	else if (currentSprite == 4)
	{
		spriteDecider = 0;
	}
	else
	{
		spriteDecider = currentSprite;
	}
	sprite.setTextureRect(sf::IntRect(spriteDecider * 32, 0, 32, 20));
	window.draw(sprite);
	if (timer.getElapsedTime() >= sf::milliseconds(200))
	{
		currentSprite++;
		timer.restart();
		if (currentSprite >= 5)
		{
			currentSprite = 0;
		}
	}

}