#include "Controleur.h"
#include <vector>
#include <locale>

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
		else if (event.key.code == Keyboard::Return)
		{
			return Scene::scenes::MENU;
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

//Création de compte
bool Controleur::ValidationCompte(std::string nickname, std::string password, std::string nom, std::string prenom, std::string courriel)
{
	//Vérification du surnom
	if (nickname.size() >= 3 && nickname.size() <= 25)
	{
		std::vector<std::string> nomCompte = modele.GetNomCompte();
		for (int i = 0; i < nomCompte.size(); ++i)
		{
			if (nickname == nomCompte.at(i))
			{
				return false;
			}
		}

		if (password.size() >= 5 && password.size() <= 15)
		{
			//Vérification si le mot de passe contient un minimum d'une minuscule, d'une majuscule et d'un chiffre
			if (!std::any_of(password.begin(), password.end(), islower) && !std::any_of(password.begin(), password.end(), isupper) && !std::any_of(password.begin(), password.end(), isdigit))
			{
				return false;
			}
			//Vérification si le mot de passe contient seulement des chiffres et des lettres
			if (std::all_of(password.begin(), password.end(), isalnum))
			{
				return false;
			}

			if (nom.size() >= 2 && nom.size() <= 25)
			{
				//Check critères
				for (int i = 0; i < nom.size(); ++i)
				{
					if (nom.at(i) == '.' || nom.at(i) == '-')
					{
						nom.erase(i,1);
					}
				}
				if (!std::all_of(nom.begin(), nom.end(), isalpha))
				{
					return false;
				}
				//Check point et trait d'union en parcourant la chiane manuellement
				if (prenom.size() >= 2 && prenom.size() <= 25)
				{
					for (int i = 0; i < prenom.size(); ++i)
					{
						if (prenom.at(i) == '.' || prenom.at(i) == '-')
						{
							prenom.erase(i, 1);
						}
					}
					if (!std::all_of(prenom.begin(), prenom.end(), isalpha))
					{
						return false;
					}

					//Peut-être revoir la vérification bizzare
					int atPosition = -1;
					int dotPosition = -1;
					for (int i = courriel.size() - 1; i > 0; --i)
					{
						if (courriel.at(i) == '@')
						{
							if (atPosition != -1)
							{
								return false;
							}
							else
							{
								atPosition = i;
							}
						}
						else if (courriel.at(i) == '.')
						{
							if (dotPosition != -1)
							{
								return false;
							}
							else
							{
								dotPosition = i;
							}
						}
						//À revoir pour les 'é' etc...
						else if (!isalnum(courriel.at(i)) && courriel.at(i) != '_' && courriel.at(i) != '-')
						{
							return false;
						}
					}
					if (atPosition == -1 || dotPosition == -1 || atPosition > dotPosition)
					{
						return false;
					}
					else if ((courriel.size() - 1) - dotPosition < 2 || (courriel.size() - 1) - dotPosition > 3)
					{
						return false;
					}
					else if (atPosition == 0 || dotPosition - atPosition == 0)
					{
						return false;
					}
				}
			}

		}
	}
	return true;
}