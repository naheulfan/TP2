#pragma once
#include <SFML\Graphics.hpp>
class Plateforme
{
public:	
	/// <summary>
	/// Initializes a new instance of the <see cref="Plateforme"/> class.
	/// </summary>
	/// <param name="baseSize">Size of the plateform.</param>
	/// <param name="basePosition">The base position.</param>
	Plateforme();
	Plateforme(float baseSize, sf::Vector2f basePosition, sf::Texture &baseTexture );
	~Plateforme();	
	/// <summary>
	/// Gets the size.
	/// </summary>
	/// <returns></returns>
	float GetSize();	
	/// <summary>
	/// Gets the position.
	/// </summary>
	/// <returns></returns>
	sf::Vector2f GetPosition();	
	/// <summary>
	/// Sets the position.
	/// </summary>
	/// <returns></returns>
	void Draw(sf::RenderWindow &window);
	void SetPosition(sf::Vector2f newPos);
private:
	sf::Vector2f position;
	float size;
	int nbBlocks;
	sf::Sprite typeBlock;
	float singleBlockSize;
};

