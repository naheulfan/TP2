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
		else if (event.key.code == Keyboard::Escape)
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
		size_t pos;
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

//Création de compte
bool Controleur::ValidationCompte(std::string nickname, std::string password, std::string nom, std::string prenom, std::string courriel)
{
	if (nickname.size() >= 3 && nickname.size() <= 25)
	{
		//Check si existe ou pas dans le txt
		/*while(readLine)
		if(nicknameTxt != nickname)
		*/

		if (password.size() >= 5 && password.size() <= 15)
		{
			//Check critères Doit contenir au moins une lettre minuscule, une majuscule, 
			//une chiffre et un caractère qui n’est ni un chiffre ni une lettre. 
			//std::any_of(password.begin(), password.end(), islower);
			//std::any_of(password.begin(), password.end(), isupper);
			//std::any_of(password.begin(), password.end(), isdigit);
			//check manuel pour un caractère spécial autre que chiffre et lettre
			if (nom.size() >= 2 && nom.size() <= 25)
			{
				//Check critères
				//!std::any_of(nom.begin(), nom.end(), isdigit);
				//Check point et trait d'union en parcourant la chiane manuellement
				if (prenom.size() >= 2 && prenom.size() <= 25)
				{
					//Check critères (comme Nom)

					//if () Check courriel
					return true;
				}

			}

		}
	}
	return false;
}