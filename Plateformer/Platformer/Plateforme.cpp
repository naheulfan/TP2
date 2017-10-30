#include "Plateforme.h"



Plateforme::Plateforme(float baseSize, sf::Vector2f basePosition, sf::Texture& texture)
{
	position = basePosition;
	size = baseSize;
	typeBlock.setTexture(texture);
	typeBlock.setPosition(position);
	nbBlocks = size / texture.getSize().x;
	singleBlockSize = texture.getSize().x;
}

Plateforme::Plateforme()
{
}

Plateforme::~Plateforme()
{
}

float Plateforme::GetSize()
{
	return size;
}
sf::Vector2f Plateforme::GetPosition()
{
	return position;
}
void Plateforme::SetPosition(sf::Vector2f newPos)
{
	position = newPos;
}
void Plateforme::Draw(sf::RenderWindow &window)
{
	float thisX = position.x;
	for (int i = 0; i < nbBlocks; i++)
	{
		window.draw(typeBlock);
		typeBlock.setPosition(sf::Vector2f(thisX, position.y));
		thisX += singleBlockSize;
	}
}