#include "Sections.h"



Sections::Sections()
{

}
Sections::Sections(int sectionNumber)
{
	texture.loadFromFile("Ressources\\Tiles\\BlockA0.png");
	if (sectionNumber == 1)
	{
		plateformes[0] = Plateforme(250, sf::Vector2f(0, 0), texture);
		plateformes[1] = Plateforme(250, sf::Vector2f(500, 0), texture);
		plateformes[2] = Plateforme(250, sf::Vector2f(250, 150), texture);
	}
	else if (sectionNumber == 2)
	{	
			plateformes[0] = Plateforme(250, sf::Vector2f(250, 0), texture);
			plateformes[1] = Plateforme(250, sf::Vector2f(0, 150), texture);
			plateformes[2] = Plateforme(250, sf::Vector2f(500, 75), texture);
	}
	else
	{
			plateformes[0] = Plateforme(250, sf::Vector2f(0, 0), texture);
			plateformes[1] = Plateforme(250, sf::Vector2f(250, 150), texture);
			plateformes[2] = Plateforme(250, sf::Vector2f(500, 150), texture);
	}
}


Sections::~Sections()
{

}

void Sections::Update()
{
	for (int i = 0; i < 3; i++)
	{
		plateformes[i].SetPosition(sf::Vector2f(plateformes[i].GetPosition().x, plateformes[i].GetPosition().y + 1));
	}
}
void Sections::Draw(sf::RenderWindow &window)
{
	for (int i = 0; i < 3; i++)
	{
		plateformes[i].Draw(window);
	}
}