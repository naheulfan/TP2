#include "Gems.h"



Gems::Gems(sf::Vector2f position)
{
	this->position = position;
}
Gems::Gems()
{

}

Gems::~Gems()
{
}

void Gems::Draw(sf::Sprite &sprite, sf::RenderWindow &window)
{
	sprite.setPosition(position);
	window.draw(sprite);
}

void Gems::Update()
{
	position.y++;
}
sf::Vector2f Gems::GetPosition()
{
	return position;
}