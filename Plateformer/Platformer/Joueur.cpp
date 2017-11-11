#include <cmath>
#include "Joueur.h"

using namespace platformer;

Joueur::Joueur() : persoRect(0, 0, TAILLE_RECT, TAILLE_RECT)
{
	jump = false;
	isFalling = false;
	isFrozen = false;
	isSlown = false;
}

Joueur::~Joueur()
{
}

bool Joueur::init(const int limiteGauche, const int limiteDroite, const String texturePath)
{
	if (!texture.loadFromFile(texturePath))
	{
		return false;
	}

	setTexture(texture);
	setTextureRect(persoRect);
	setOrigin(TAILLE_RECT / 2, TAILLE_RECT /2);

	this->limiteGauche = limiteGauche + TAILLE_RECT / 4;
	this->limiteDroite = limiteDroite - TAILLE_RECT / 4;

	return true;
}

void Joueur::move(const int direction)
{
	if (SlimeTimer.getElapsedTime() < sf::seconds(3) && isSlown)
	{
		vitesse = 0.5;
	}
	else if (SlimeTimer.getElapsedTime() >= sf::seconds(3))
	{
		vitesse = 3;
		isSlown = false;
	}
	if (direction == 1)
	{
		Sprite::move(vitesse, 0);
	}
	else if (direction == -1)
	{
		Sprite::move(-vitesse, 0);
	}


	//Test sur les limites de l'écran
	if (getPosition().x < limiteGauche)
	{
		setPosition(limiteDroite, getPosition().y);
	}
	else if (getPosition().x > limiteDroite)
	{
		setPosition(limiteGauche, getPosition().y);
	}
}

void Joueur::Jump()
{
	if (jump)
	{
		Sprite::move(0, -vitesse * 2);
	}
	else
	{
		jumpClock.restart();
	}
	if (GetJumpClock() > 0.6f)
	{
		jump = false;
		jumpClock.restart();
		isFalling = true;
	}
}

void Joueur::Gravity()
{
	if(isFalling)
		Sprite::move(0, 3 * 2);
	else
	{
		Sprite::move(0, 1);
	}
}

bool Joueur::CollisionPlateforme(Vector2f pos, int width, int height)
{
	pos.y -= TAILLE_RECT/2;
	if (!GetJump())
	{
		if (getPosition().x <= pos.x + width && getPosition().x >= pos.x)
		{	
			if (getPosition().y <= pos.y + height && getPosition().y >= pos.y)
			{
				setPosition(getPosition().x, pos.y);
				isFalling = false;
				return true;
			}
		}
	}
	return false;
}
bool Joueur::CollisionEnnemis(Vector2f pos, int width, int height)
{
	if (getPosition().x <= pos.x + width && getPosition().x >= pos.x)
	{
		if (getPosition().y <= pos.y + height && getPosition().y >= pos.y)
		{
			return true;
		}
	}
	return false;
}

bool Joueur::GetJump() const
{
	return jump;
}

void Joueur::SetJump(bool value)
{
	jump = value;
}

float Joueur::GetJumpClock() const
{
	return jumpClock.getElapsedTime().asSeconds();
}

bool Joueur::GetIsFalling() const
{
	return isFalling;
}

void Joueur::SetIsFalling(bool value)
{
	isFalling = value;
}
void Joueur::Freeze()
{
	isFrozen = true;
	texture.loadFromFile("Ressources\\Sprites\\Player\\IceBlock.png");

}
bool Joueur::GetIsFrozen()
{
	return isFrozen;
}
void Joueur::SlimeSlow()
{
	SlimeTimer.restart();
	isSlown = true;
}