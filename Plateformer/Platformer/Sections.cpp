#include "Sections.h"



Sections::Sections()
{

}
Sections::Sections(int sectionNumber)
{
	if (sectionNumber == 1)
	{
		plateformes[0].SetPosition(sf::Vector2f(0, 0));
		plateformes[1].SetPosition(sf::Vector2f(200, 0));
		plateformes[2].SetPosition(sf::Vector2f(100, 75));
	}
	else if (sectionNumber == 2)
	{	
			plateformes[0].SetPosition(sf::Vector2f(100, 0));
			plateformes[1].SetPosition(sf::Vector2f(0, 75));
			plateformes[2].SetPosition(sf::Vector2f(200, 75));
	}
	else
	{
			plateformes[0].SetPosition(sf::Vector2f(0, 0));
			plateformes[1].SetPosition(sf::Vector2f(100, 75));
			plateformes[2].SetPosition(sf::Vector2f(200, 75));
	}
}


Sections::~Sections()
{

}

void Sections::Update()
{

}