#include "Ennemi.h"



Ennemi::Ennemi(sf::Vector2f basePos,sf::Texture &texture)
{
	position = basePos;
	sprite.setTexture(texture);

}
void Ennemi::Draw(sf::RenderWindow &window)
{
	sprite.setPosition(position);
	window.draw(sprite);
}
Ennemi::~Ennemi()
{
}
sf::Vector2f Ennemi::Getposition()
{
	return position;
}
void Ennemi::SetPosition(sf::Vector2f newPos)
{
	position = newPos;
}