#include "Chevalier.h"



Chevalier::Chevalier(sf::Vector2f position, sf::Texture &texture, float platformSize) : Ennemi(position, texture, platformSize)
{
	goingRight = true;
	speed = 1;
	currentSprite = 0;
	timer.restart();
	sprite.setOrigin(sf::Vector2f(32, 32));
	typeEnnemi = 1;
}
Chevalier::Chevalier()
{
}

Chevalier::~Chevalier()
{
}
void Chevalier::Update()
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
void Chevalier::Draw(sf::RenderWindow &window)
{
	sprite.setPosition(position);
	if (currentSprite == 4)
	{
		sprite.setTextureRect(sf::IntRect(3 * 64, 0, 128, 64));
	}
	else
	{
		sprite.setTextureRect(sf::IntRect(currentSprite * 64, 0, 64, 64));
	}
	window.draw(sprite);
	if (timer.getElapsedTime() >= sf::milliseconds(200))
	{
		currentSprite++;
		timer.restart();
		if (currentSprite >= 3)
		{
			currentSprite = 0;
		}
	}

}
void Chevalier::Attack()
{
	currentSprite = 4;
}

