#include "Controleur.h"

using namespace platformer;

Controleur *Controleur::instance = nullptr;

Controleur::Controleur()
{

}

Controleur* Controleur::GetInstance()
{
	if (!instance)
		instance = new Controleur();
	return instance;
}

void Controleur::Release()
{
	delete instance;
	instance = nullptr;
}

Scene::scenes Controleur::RequeteChangerScene(Scene::scenes sceneCourante, Event event)
{
	if (sceneCourante == Scene::scenes::MENU)
	{
		//Les scenes que Menu peut se rendre
		if (event.key.code == Keyboard::Space)
		{
			return Scene::scenes::TITRE;
		}
	}
	return sceneCourante;
}