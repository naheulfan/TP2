#pragma once
#include "Slime.h"
#include "Dragon.h"
#include "Chevalier.h"
#include "Ennemi.h"
#include <SFML\Graphics.hpp>
class FabriqueEnnemi
{
public:
	static Ennemi* GenerateEnnemi(int ennemiId, sf::Vector2f position, float platformSize);
private:
	FabriqueEnnemi();
};

