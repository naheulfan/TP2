#pragma once
#include "Ennemi.h"
class Slime : public Ennemi
{
public:
	Slime::Slime();
	Slime(sf::Vector2f position, sf::Texture &texture, float platformSize);
	~Slime();
	void Update();
	void Draw(sf::RenderWindow &window);
	void Attack() override;
private:
	float speed;
	int currentSprite;
};

