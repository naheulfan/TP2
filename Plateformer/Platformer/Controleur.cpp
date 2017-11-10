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
	else if (sceneCourante == Scene::scenes::TITRE && event.key.code == Keyboard::Escape)
	{
		return Scene::scenes::MENU;
	}
	else if (sceneCourante == Scene::scenes::MENU)
	{
		//Les scenes que Menu peut se rendre
		if (event.key.code == Keyboard::Space)
		{
			return Scene::scenes::TITRE;
		}
		else if (event.key.code == Keyboard::S)
		{
			return Scene::scenes::SCORE;
		}
		else if (event.key.code == Keyboard::G)
		{
			return Scene::scenes::GESTION_COMPTE;
		}
	}
	else if (sceneCourante == Scene::scenes::GESTION_COMPTE)
	{
		if (event.key.code == Keyboard::E)
		{
			return Scene::scenes::EFFACER_COMPTE;
		}
		else if (event.key.code == Keyboard::M)
		{
			return Scene::scenes::MODIFIER_COMPTE;
		}
		else if (event.key.code == Keyboard::C)
		{
			return Scene::scenes::CREER_COMPTE;
		}
		else if (event.key.code == Keyboard::P)
		{
			return Scene::scenes::MENU;
		}
	}
	else if (sceneCourante == Scene::scenes::CREER_COMPTE)
	{
		if (event.key.code == Keyboard::Escape)
		{
			return Scene::scenes::GESTION_COMPTE;
		}
	}
	return sceneCourante;
}

bool Controleur::VerificationCompte(std::string nickname, std::string password)
{
		std::string* compte = nullptr;
		std::vector<std::string> nomCompte = modele.GetNomCompte();
		for (int i = 0; i < nomCompte.size(); ++i)
		{
			if (nickname == nomCompte.at(i))
			{
				compte = modele.DonneeCompte(nickname);
			}
		}
		if (compte == nullptr)
		{
			return false;
		}
		else if (compte[0] == nickname && compte[1] == password)
		{
			return true;
		}

		return false;
}

//Cr�ation de compte
bool Controleur::ValidationCompte(std::string nickname, std::string password, std::string nom, std::string prenom, std::string courriel)
{
	bool compteOk = false;
	if (nickname.size() >= 3 && nickname.size() <= 25)
	{
		//Check si existe ou pas dans le .txt
		std::vector<std::string> nomCompte = modele.GetNomCompte();
		for (int i = 0; i < nomCompte.size(); ++i)
		{
			if (nickname == nomCompte.at(i))
			{
				compteOk = true;
			}
		}

		if (password.size() >= 5 && password.size() <= 15 && compteOk == true)
		{
			//Check crit�res Doit contenir au moins une lettre minuscule, une majuscule, 
			//une chiffre et un caract�re qui n�est ni un chiffre ni une lettre. 
			if (!std::any_of(password.begin(), password.end(), islower) && !std::any_of(password.begin(), password.end(), isupper))
			{
				compteOk = false;
			}
			if (!std::any_of(password.begin(), password.end(), isdigit))
			{
				compteOk = false;
			}
			//check manuel pour un caract�re sp�cial autre que chiffre et lettre

			if (nom.size() >= 2 && nom.size() <= 25)
			{
				//Check crit�res
				//!std::any_of(nom.begin(), nom.end(), isdigit);
				//Check point et trait d'union en parcourant la chiane manuellement
				if (prenom.size() >= 2 && prenom.size() <= 25)
				{
					//Check crit�res (comme Nom)

					//if () Check courriel
					//return true;
				}

			}

		}
	}
	return compteOk;
}