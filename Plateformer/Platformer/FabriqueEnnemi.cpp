#include "FabriqueEnnemi.h"



Ennemi* FabriqueEnnemi::GenerateDragon(int ennemiId, sf::Vector2f position, float platformSize)
{
	sf::Texture DragonTexture;
	sf::Texture ChevalierTexture;
	sf::Texture SlimeTexture;
	DragonTexture.loadFromFile("Ressources\\Sprites\\Dragon.png");
	ChevalierTexture.loadFromFile("Ressources\\Sprites\\Paladin.png");
	SlimeTexture.loadFromFile("Ressources\\Sprites\\Slime.png");
	if (ennemiId == 0)
	{
		return new Dragon(position, DragonTexture, platformSize);
	}
	else if (ennemiId == 1)
	{
		return new Chevalier(position, ChevalierTexture, platformSize);
	}
	else if (ennemiId == 2)
	{
		return new Slime(position, SlimeTexture, platformSize);
	}
}

FabriqueEnnemi::FabriqueEnnemi()
{

}

