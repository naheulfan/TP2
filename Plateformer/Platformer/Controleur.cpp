#include "Controleur.h"
#include <vector>

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
	if (sceneCourante == Scene::scenes::NIVEAU1 && event.key.code == Keyboard::Escape)
	{
		return Scene::scenes::MENU;
	}
	if (sceneCourante == Scene::scenes::MENU)
	{
		//Les scenes que Menu peut se rendre
		if (event.key.code == Keyboard::Space)
		{
			return Scene::scenes::TITRE;
		}
		else if (event.key.code == Keyboard::Tab)
		{
			return Scene::scenes::TITRE;
		}
		else if (event.key.code == Keyboard::C)
		{
			return Scene::scenes::TITRE;
		}
	}
	return sceneCourante;
}

bool Controleur::VerificationCompte(std::string nom, std::string password)
{
		size_t pos;
		std::string* compte;
		std::vector<std::string> nomCompte = modele.GetNomCompte();
		for (int i = 0; i < modele.GetSize(); ++i)
		{
			if (nom == nomCompte.at(i))
			{
				compte = modele.DonneeCompte(i);
			}
		}
		if (compte[0] == nom && compte[1] == password)
		{
			return true;
		}
		else
		{
			return false;
		}
}