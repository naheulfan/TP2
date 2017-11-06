#include "Ennemi.h"



Ennemi::Ennemi(sf::Vector2f basePos,sf::Texture &texture, float plateformSize)
{
	position = basePos;
	sprite.setTexture(texture);
	bounds[0] = basePos.x;
	bounds[1] = bounds[0] + plateformSize;


}
void Ennemi::Draw(sf::RenderWindow &window)
{
	sprite.setPosition(position);
	window.draw(sprite);
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