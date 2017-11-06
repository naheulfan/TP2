#pragma once
#include "Ennemi.h"
class Dragon : public Ennemi
{
public:
	Dragon::Dragon();
	Dragon(sf::Vector2f position, sf::Texture &texture, float platformSize);
	~Dragon();
	void Update();

};

