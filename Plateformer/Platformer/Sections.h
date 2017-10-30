#pragma once
#include "Plateforme.h"
#include <SFML\Graphics.hpp>
class Sections
{
public:
	Sections();	
	/// <summary>
	/// Initializes a new instance of the <see cref="Sections"/> class.
	/// </summary>
	/// <param name="sectionNumber">The section number, between 1 and 3. An invalid number returns section #3.</param>
	Sections(int sectionNumber);
	~Sections();
	void Update();
	void Draw(sf::RenderWindow &window);
private:
	sf::Texture texture;
	Plateforme plateformes[3];
};

