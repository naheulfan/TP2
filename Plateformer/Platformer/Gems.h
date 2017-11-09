#pragma once
#include <SFML\Graphics.hpp>
class Gems
{
public:
	Gems(sf::Vector2f position);
	Gems();
	~Gems();
	void Draw(sf::Sprite &sprite, sf::RenderWindow &window); //pour un modèle flyweight
	void Update();
	sf::Vector2f GetPosition();
	void SetPosition(sf::Vector2f newPos);
private:
	sf::Vector2f position;
	sf::Sprite sprite;
};

