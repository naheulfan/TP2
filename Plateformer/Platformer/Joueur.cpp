#include <cmath>
#include "Joueur.h"

using namespace platformer;

Joueur::Joueur() : persoRect(0, 0, TAILLE_RECT, TAILLE_RECT)
{
	jump = false;
	isFalling = false;
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
		setPosition(limiteGauche, getPosition().y);
	}
	else if (getPosition().x > limiteDroite)
	{
		setPosition(limiteDroite, getPosition().y);
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
	}
}

void Joueur::Gravity(int size, float posX, float posY)
{
	if (isFalling)
	{
		//Check avec collisionSphere ?
		if (getPosition().x > posX && getPosition().x < posX + size  && lround(getPosition().y) == lround(posY))
		{
			setPosition(getPosition().x, posY);
			isFalling = false;
		}

		Sprite::move(0, vitesse * 2);
	}
}

bool Joueur::Collision(CollisionSphere &autreSphere)
{
	CollisionSphere sphere = CollisionSphere(texture.getSize().x / 2, getPosition().x, getPosition().y);
	bool reponse = sphere.verifierCollision(autreSphere);
	return reponse;
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