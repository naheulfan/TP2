#include "Controleur.h"
#include <vector>
#include <locale>

using namespace platformer;

//L'instance du controleur
Controleur *Controleur::instance = nullptr;

Controleur::Controleur()
{
}

/// <summary>
/// Initialise l'instance et la retourne
/// </summary>
///<return>Retourne l'instance du controleur</return>
Controleur* Controleur::GetInstance()
{
	if (!instance)
		instance = new Controleur();
	return instance;
}

/// <summary>
/// Relâche l'instance du controleur
/// </summary>
void Controleur::Release()
{
	delete instance;
	instance = nullptr;
}

/// <summary>
/// Fait une demande pour changer de scène dépandant de la scène et de l'évènement
/// </summary>
/// <param name="sceneCourante">Scène courante</param>
/// <param name="event">Évènement impliqué</param>
///<return>Retourne la nouvelle scène</return>
Scene::scenes Controleur::RequeteChangerScene(Scene::scenes sceneCourante, Event event)
{
	//Retourne au menu si la scène courrante est le niveau 1 et que l'évènement est un "Escape"
	if (sceneCourante == Scene::scenes::NIVEAU1 && event.key.code == Keyboard::Escape)
	{
		return Scene::scenes::MENU;
	}
	//Si la scène est l'écran titre
	else if (sceneCourante == Scene::scenes::TITRE)
	{
		//Retourne à l'écran de menu si la touche appuyé est "Escape"
		if (event.key.code == Keyboard::Escape)
		{
			return Scene::scenes::MENU;
		}
		//Va vers le niveau 1 si l'évènement est de type "Return"
		else if (event.key.code == Keyboard::Return)
		{
			return Scene::scenes::NIVEAU1;
		}
	}
	//Si la scène est le menu
	else if (sceneCourante == Scene::scenes::MENU)
	{
		//Va à l'écran titre si la touche appuyé est "Espace"
		if (event.key.code == Keyboard::Space)
		{
			return Scene::scenes::TITRE;
		}
		//Va à l'écran de score si la touche appuyé est "S"
		else if (event.key.code == Keyboard::S)
		{
			return Scene::scenes::SCORE;
		}
		//Va à l'écran gestion de compte si la touche appuyé est "G"
		else if (event.key.code == Keyboard::G)
		{
			return Scene::scenes::GESTION_COMPTE;
		}
	}
	//Si la scène est l'écran de gestion de compte
	else if (sceneCourante == Scene::scenes::GESTION_COMPTE)
	{
		//Va vers l'écran d'effacement de compte si la touche appuyé est "E"
		if (event.key.code == Keyboard::E)
		{
			return Scene::scenes::EFFACER_COMPTE;
		}
		//Va vers l'écran de modifiaction de compte si la touche appuyé est "D"
		else if (event.key.code == Keyboard::D)
		{
			return Scene::scenes::MODIFIER_COMPTE;
		}
		//Va vers l'écran de création de compte si la touche appuyé est "C"
		else if (event.key.code == Keyboard::C)
		{
			return Scene::scenes::CREER_COMPTE;
		}
		//Retourne à l'écran de menu si la touche appuyé est "M"
		else if (event.key.code == Keyboard::M)
		{
			return Scene::scenes::MENU;
		}
	}
	//Si la scène est l'écran de création de compte
	else if (sceneCourante == Scene::scenes::CREER_COMPTE)
	{
		//Retourne vers l'écran de gestion de compte si la touche appuyé est "Escape"
		if (event.key.code == Keyboard::Escape)
		{
			return Scene::scenes::GESTION_COMPTE;
		}
		//Retourne vers l'écran de gestion de compte si l'évènement est de type "Return"
		else if (event.key.code == Keyboard::Return)
		{
			return Scene::scenes::GESTION_COMPTE;
		}
	}
	//Si la scène est l'écran de modification de compte
	else if (sceneCourante == Scene::scenes::MODIFIER_COMPTE)
	{
		//Retourne vers l'écran de gestion de compte si l'évènement est de type "Return"
		if (event.key.code == Keyboard::Return)
		{
			return Scene::scenes::GESTION_COMPTE;
		}
		//Retourne à l'écran de gestion de compte si la touche appuyé est "Escape"
		else if (event.key.code == Keyboard::Escape)
		{
			return Scene::scenes::GESTION_COMPTE;
		}
	}
	//Si la scène est l'écran d'effacement de compte
	else if (sceneCourante == Scene::scenes::EFFACER_COMPTE)
	{
		//Retourne vers l'écran de gestion de compte si l'évènement est de type "Return"
		if (event.key.code == Keyboard::Return)
		{
			return Scene::scenes::GESTION_COMPTE;
		}
		//Retourne à l'écran de gestion de compte si la touche appuyé est "Escape"
		else if (event.key.code == Keyboard::Escape)
		{
			return Scene::scenes::GESTION_COMPTE;
		}
	}
	//Si la demande ne rentre dans aucun cas on retourne la scène courante
	return sceneCourante;
}

/// <summary>
/// Vérifie si le compte existe et que le mot de passe est valide
/// </summary>
/// <param name="nickname">Surnom du joueur</param>
/// <param name="password">Mot de passe du joueur</param>
///<return>Retourne true si le compte existe</return>
bool Controleur::VerificationCompte(std::string nickname, std::string password)
{
	std::string* compte = nullptr;
	std::vector<std::string> nomCompte = modele.GetNomCompte();
	for (int i = 0; i < nomCompte.size(); ++i)
	{
		//Vérifie si le compte existe
		if (nickname == nomCompte.at(i))
		{
			//Obtient les données du compte
			compte = modele.DonneeCompte(nickname);
		}
	}
	//Retourne false si le compte n'existe pas
	if (compte == nullptr)
	{
		return false;
	}
	//Retourne true si le mot de passe est valide
	else if (compte[0] == nickname && compte[1] == password)
	{
		return true;
	}

	return false;
}

/// <summary>
/// Effectue la vérification pour la création de compte
/// </summary>
/// <param name="nickname">Surnom du joueur</param>
/// <param name="password">Mot de passe du joueur</param>
/// <param name="nom">Nom du joueur</param>
/// <param name="prenom">Prénom du joueur</param>
/// <param name="courriel">Courriel du joueur</param>
///<return>Retourne true si les critères de vérification sont respectés</return>
bool Controleur::ValidationCompte(std::string nickname, std::string password, std::string nom, std::string prenom, std::string courriel)
{
	//Vérification de la taille du surnom
	if (nickname.size() >= 3 && nickname.size() <= 25)
	{
		//Vérification si le compte existe déjà
		std::vector<std::string> nomCompte = modele.GetNomCompte();
		for (int i = 0; i < nomCompte.size(); ++i)
		{
			if (nickname == nomCompte.at(i))
			{
				return false;
			}
		}
		//Validation du reste des éléments
		return ValidationInfoCompte(password, nom, prenom, courriel);
	}
	else
	{
		return false;
	}
}

/// <summary>
/// Effectue la vérification pour la création de compte
/// </summary>
/// <param name="password">Mot de passe du joueur</param>
/// <param name="nom">Nom du joueur</param>
/// <param name="prenom">Prénom du joueur</param>
/// <param name="courriel">Courriel du joueur</param>
///<return>Retourne true si les critères de vérification sont respectés</return>
bool Controleur::ValidationInfoCompte(std::string password, std::string nom, std::string prenom, std::string courriel)
{
	//Vérification de la taille du mot de passe
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
		//Vérification de la taille du nom
		if (nom.size() >= 2 && nom.size() <= 25)
		{
			for (int i = 0; i < nom.size(); ++i)
			{
				//Enlève les "." et les "-" du nom s'il y en a
				if (nom.at(i) == '.' || nom.at(i) == '-')
				{
					nom.erase(i, 1);
				}
			}
			//Vérification si le reste des caractères du nom sont des alphanumériques
			if (!std::all_of(nom.begin(), nom.end(), isalpha))
			{
				return false;
			}
			//Vérification de la taille du prénom
			if (prenom.size() >= 2 && prenom.size() <= 25)
			{
				for (int i = 0; i < prenom.size(); ++i)
				{
					//Enlève les "." et les "-" du nom s'il y en a
					if (prenom.at(i) == '.' || prenom.at(i) == '-')
					{
						prenom.erase(i, 1);
					}
				}
				//Vérification si le reste des caractères du prénom sont des alphanumériques
				if (!std::all_of(prenom.begin(), prenom.end(), isalpha))
				{
					return false;
				}

				int atPosition = -1;
				int dotPosition = -1;
				for (int i = courriel.size() - 1; i > 0; --i)
				{
					//Vérification de la position du "@"
					if (courriel.at(i) == '@')
					{
						//Si il n'y a pas de "@"
						if (atPosition != -1)
						{
							return false;
						}
						else
						{
							atPosition = i;
						}
					}
					//Vérification de la position du "."
					else if (courriel.at(i) == '.')
					{
						//Si il n'y a pas de "."
						if (dotPosition != -1)
						{
							return false;
						}
						else
						{
							dotPosition = i;
						}
					}
					//Vérification si le reste des caractères du courriel sont des alphanumérique ou des "_" ou des "-"
					else if (!isalnum(courriel.at(i)) && courriel.at(i) != '_' && courriel.at(i) != '-')
					{
						return false;
					}
				}
				//Vérification si le "." est placer après le "@"
				if (atPosition == -1 || dotPosition == -1 || atPosition > dotPosition)
				{
					return false;
				}
				//Vérification s'il y a un domaine
				else if ((courriel.size() - 1) - dotPosition < 2 || (courriel.size() - 1) - dotPosition > 3)
				{
					return false;
				}
				//Vérification s'il y a quelque chose devant le "@" et entre le "@" et le "."
				else if (atPosition == 0 || dotPosition - atPosition == 0)
				{
					return false;
				}
			}
		}
	}
	return true;
}

/// <summary>
/// Effectue l'effacement d'un compte
/// </summary>
/// <param name="nickname">Surnom du joueur</param>
/// <param name="password">Mot de passe du joueur</param>
///<return>Retourne true si le compte a été effacé</return>
bool Controleur::RequeteEffacerCompte(std::string nickname, std::string password)
{
	//Numéro de la ligne du compte
	int noCompte;
	if (VerificationCompte(nickname, password))
	{
		//Demande au modèle d'effacer le compte
		noCompte = modele.NoCompte(nickname);
		modele.EffacerCompte(noCompte);
	}
	return true;
}

/// <summary>
/// Vérifie su le compte existe
/// </summary>
/// <param name="nickname">Surnom du joueur</param>
///<return>Retourne true si le compte existe</return>
bool Controleur::CompteExiste(std::string nickname)
{
	bool compteExiste = false;
	//Demande au modèle tous les noms de compte
	std::vector<std::string> nomCompte = modele.GetNomCompte();
	for (int i = 0; i < nomCompte.size(); i++)
	{
		//Vérifie si le compte existe
		if (nomCompte.at(i) == nickname)
		{
			compteExiste = true;
		}
	}
	return compteExiste;
}

/// <summary>
/// Effectue la vérification et la modification de compte
/// </summary>
/// <param name="nickname">Surnom du joueur</param>
/// <param name="password">Mot de passe du joueur</param>
/// <param name="nom">Nouveau nom du joueur</param>
/// <param name="prenom">Nouveau prénom du joueur</param>
/// <param name="courriel">Nouveau courriel du joueur</param>
///<return>Retourne true si la modification c'est bien déroulée</return>
bool Controleur::RequeteModificationCompte(std::string nickname, std::string password, std::string nom, std::string prenom, std::string courriel)
{
	//Vérification des nouvelles données du compte 
	if (ValidationInfoCompte(password, nom, prenom, courriel))
	{
		//Envoie des données au modèle
		modele.ModifierCompte(nickname, password, nom, prenom, courriel);
	}
	return true;
}
