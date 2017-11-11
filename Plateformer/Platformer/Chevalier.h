#pragma once
#include "Ennemi.h"
class Chevalier : public Ennemi
{
public:
	Chevalier::Chevalier();
	Chevalier(sf::Vector2f position, sf::Texture &texture, float platformSize);
	~Chevalier();
	void Update();
	void Draw(sf::RenderWindow &window);
	void Attack() override;

private:
	float speed;
	int currentSprite;
};

