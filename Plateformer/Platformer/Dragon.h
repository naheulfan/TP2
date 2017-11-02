#pragma once
#include "Ennemi.h"
class Dragon : public Ennemi
{
public:
	Dragon(sf::Vector2f position, sf::Vector2f &texture);
	~Dragon();
	void Update();

};

