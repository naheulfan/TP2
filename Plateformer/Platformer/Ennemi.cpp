#include "Ennemi.h"



Ennemi::Ennemi(sf::Vector2f basePos ,sf::Texture &texture, float plateformSize)
{
	position = sf::Vector2f(basePos.x, basePos.y - texture.getSize().y / 2);
	sprite.setTexture(texture);
	bounds[0] = basePos.x;
	bounds[1] = basePos.x + plateformSize;


}

Ennemi::Ennemi()
{

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