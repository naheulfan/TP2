#pragma once

class CollisionSphere
{
public:
	CollisionSphere();
	CollisionSphere(const float rayon, const float posX, const float posY);
	bool verifierCollision(const CollisionSphere &autreSphere) const;

	float getRayon() const;
	float getPosX() const;
	float getPosY() const;

private:
	float rayon;
	float posX;
	float posY;
};


