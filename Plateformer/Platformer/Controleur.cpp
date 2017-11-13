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
/// Rel�che l'instance du controleur
/// </summary>
void Controleur::Release()
{
	delete instance;
	instance = nullptr;
}

/// <summary>
/// Fait une demande pour changer de sc�ne d�pandant de la sc�ne et de l'�v�nement
/// </summary>
/// <param name="sceneCourante">Sc�ne courante</param>
/// <param name="event">�v�nement impliqu�</param>
///<return>Retourne la nouvelle sc�ne</return>
Scene::scenes Controleur::RequeteChangerScene(Scene::scenes sceneCourante, Event event)
{
	//Retourne au menu si la sc�ne courrante est le niveau 1 et que l'�v�nement est un "Escape"
	if (sceneCourante == Scene::scenes::NIVEAU1 && event.key.code == Keyboard::Escape)
	{
		return Scene::scenes::MENU;
	}
	//Si la sc�ne est l'�cran titre
	else if (sceneCourante == Scene::scenes::TITRE)
	{
		//Retourne � l'�cran de menu si la touche appuy� est "Escape"
		if (event.key.code == Keyboard::Escape)
		{
			return Scene::scenes::MENU;
		}
		//Va vers le niveau 1 si l'�v�nement est de type "Return"
		else if (event.key.code == Keyboard::Return)
		{
			return Scene::scenes::NIVEAU1;
		}
	}
	//si la sc�ne est l'�cran de scores
	else if (sceneCourante == Scene::scenes::SCORE)
	{
		//Retourne � l'�cran de menu si la touche appuy� est "Escape"
		if (event.key.code == Keyboard::Escape)
		{
			return Scene::scenes::MENU;
		}
	}
	//Si la sc�ne est le menu
	else if (sceneCourante == Scene::scenes::MENU)
	{
		//Va � l'�cran titre si la touche appuy� est "Espace"
		if (event.key.code == Keyboard::Space)
		{
			return Scene::scenes::TITRE;
		}
		//Va � l'�cran de score si la touche appuy� est "S"
		else if (event.key.code == Keyboard::S)
		{
			return Scene::scenes::SCORE;
		}
		//Va � l'�cran gestion de compte si la touche appuy� est "G"
		else if (event.key.code == Keyboard::G)
		{
			return Scene::scenes::GESTION_COMPTE;
		}
		else if (event.key.code == Keyboard::S)
		{
			return Scene::scenes::SCORE;
		}
	}
	//Si la sc�ne est l'�cran de gestion de compte
	else if (sceneCourante == Scene::scenes::GESTION_COMPTE)
	{
		//Va vers l'�cran d'effacement de compte si la touche appuy� est "E"
		if (event.key.code == Keyboard::E)
		{
			return Scene::scenes::EFFACER_COMPTE;
		}
		//Va vers l'�cran de modifiaction de compte si la touche appuy� est "D"
		else if (event.key.code == Keyboard::D)
		{
			return Scene::scenes::MODIFIER_COMPTE;
		}
		//Va vers l'�cran de cr�ation de compte si la touche appuy� est "C"
		else if (event.key.code == Keyboard::C)
		{
			return Scene::scenes::CREER_COMPTE;
		}
		//Retourne � l'�cran de menu si la touche appuy� est "M"
		else if (event.key.code == Keyboard::M)
		{
			return Scene::scenes::MENU;
		}
	}
	//Si la sc�ne est l'�cran de cr�ation de compte
	else if (sceneCourante == Scene::scenes::CREER_COMPTE)
	{
		//Retourne vers l'�cran de gestion de compte si la touche appuy� est "Escape"
		if (event.key.code == Keyboard::Escape)
		{
			return Scene::scenes::GESTION_COMPTE;
		}
		//Retourne vers l'�cran de gestion de compte si l'�v�nement est de type "Return"
		else if (event.key.code == Keyboard::Return)
		{
			return Scene::scenes::GESTION_COMPTE;
		}
	}
	//Si la sc�ne est l'�cran de modification de compte
	else if (sceneCourante == Scene::scenes::MODIFIER_COMPTE)
	{
		//Retourne vers l'�cran de gestion de compte si l'�v�nement est de type "Return"
		if (event.key.code == Keyboard::Return)
		{
			return Scene::scenes::GESTION_COMPTE;
		}
		//Retourne � l'�cran de gestion de compte si la touche appuy� est "Escape"
		else if (event.key.code == Keyboard::Escape)
		{
			return Scene::scenes::GESTION_COMPTE;
		}
	}
	//Si la sc�ne est l'�cran d'effacement de compte
	else if (sceneCourante == Scene::scenes::EFFACER_COMPTE)
	{
		//Retourne vers l'�cran de gestion de compte si l'�v�nement est de type "Return"
		if (event.key.code == Keyboard::Return)
		{
			return Scene::scenes::GESTION_COMPTE;
		}
		//Retourne � l'�cran de gestion de compte si la touche appuy� est "Escape"
		else if (event.key.code == Keyboard::Escape)
		{
			return Scene::scenes::GESTION_COMPTE;
		}
	}
	//Si la demande ne rentre dans aucun cas on retourne la sc�ne courante
	return sceneCourante;
}

/// <summary>
/// V�rifie si le compte existe et que le mot de passe est valide
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
		//V�rifie si le compte existe
		if (nickname == nomCompte.at(i))
		{
			//Obtient les donn�es du compte
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
/// Effectue la v�rification pour la cr�ation de compte
/// </summary>
/// <param name="nickname">Surnom du joueur</param>
/// <param name="password">Mot de passe du joueur</param>
/// <param name="nom">Nom du joueur</param>
/// <param name="prenom">Pr�nom du joueur</param>
/// <param name="courriel">Courriel du joueur</param>
///<return>Retourne true si les crit�res de v�rification sont respect�s</return>
bool Controleur::ValidationCompte(std::string nickname, std::string password, std::string nom, std::string prenom, std::string courriel)
{
	//V�rification de la taille du surnom
	if (nickname.size() >= 3 && nickname.size() <= 25)
	{
		//V�rification si le compte existe d�j�
		std::vector<std::string> nomCompte = modele.GetNomCompte();
		for (int i = 0; i < nomCompte.size(); ++i)
		{
			if (nickname == nomCompte.at(i))
			{
				return false;
			}
		}
		//Validation du reste des �l�ments
		return ValidationInfoCompte(password, nom, prenom, courriel);
	}
	else
	{
		return false;
	}
}

/// <summary>
/// Effectue la v�rification pour la cr�ation de compte
/// </summary>
/// <param name="password">Mot de passe du joueur</param>
/// <param name="nom">Nom du joueur</param>
/// <param name="prenom">Pr�nom du joueur</param>
/// <param name="courriel">Courriel du joueur</param>
///<return>Retourne true si les crit�res de v�rification sont respect�s</return>
bool Controleur::ValidationInfoCompte(std::string password, std::string nom, std::string prenom, std::string courriel)
{
	//V�rification de la taille du mot de passe
	if (password.size() >= 5 && password.size() <= 15)
	{
		//V�rification si le mot de passe contient un minimum d'une minuscule, d'une majuscule et d'un chiffre
		if (!std::any_of(password.begin(), password.end(), islower) || !std::any_of(password.begin(), password.end(), isupper) || !std::any_of(password.begin(), password.end(), isdigit))
		{
			return false;
		}
		//V�rification si le mot de passe contient seulement des chiffres et des lettres
		if (std::all_of(password.begin(), password.end(), isalnum))
		{
			return false;
		}
		//V�rification de la taille du nom
		if (nom.size() >= 2 && nom.size() <= 25)
		{
			for (int i = 0; i < nom.size(); ++i)
			{
				//Enl�ve les "." et les "-" du nom s'il y en a
				if (nom.at(i) == '.' || nom.at(i) == '-')
				{
					nom.erase(i, 1);
				}
			}
			//V�rification si le reste des caract�res du nom sont des alphanum�riques
			if (!std::all_of(nom.begin(), nom.end(), isalpha))
			{
				return false;
			}
			//V�rification de la taille du pr�nom
			if (prenom.size() >= 2 && prenom.size() <= 25)
			{
				for (int i = 0; i < prenom.size(); ++i)
				{
					//Enl�ve les "." et les "-" du nom s'il y en a
					if (prenom.at(i) == '.' || prenom.at(i) == '-')
					{
						prenom.erase(i, 1);
					}
				}
				//V�rification si le reste des caract�res du pr�nom sont des alphanum�riques
				if (!std::all_of(prenom.begin(), prenom.end(), isalpha))
				{
					return false;
				}

				int atPosition = -1;
				int dotPosition = -1;
				for (int i = courriel.size() - 1; i > 0; --i)
				{
					//V�rification de la position du "@"
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
					//V�rification de la position du "."
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
					//V�rification si le reste des caract�res du courriel sont des alphanum�rique ou des "_" ou des "-"
					else if (!isalnum(courriel.at(i)) && courriel.at(i) != '_' && courriel.at(i) != '-')
					{
						return false;
					}
				}
				//V�rification si le "." est placer apr�s le "@"
				if (atPosition == -1 || dotPosition == -1 || atPosition > dotPosition)
				{
					return false;
				}
				//V�rification s'il y a un domaine
				else if ((courriel.size() - 1) - dotPosition < 2 || (courriel.size() - 1) - dotPosition > 3)
				{
					return false;
				}
				//V�rification s'il y a quelque chose devant le "@" et entre le "@" et le "."
				else if (atPosition == 0 || dotPosition - atPosition == 1)
				{
					return false;
				}
			}
			else
			{
				return false;
			}
		}
		else
		{
			return false;
		}
	}
	return true;
}

/// <summary>
/// Effectue l'effacement d'un compte
/// </summary>
/// <param name="nickname">Surnom du joueur</param>
/// <param name="password">Mot de passe du joueur</param>
///<return>Retourne true si le compte a �t� effac�</return>
bool Controleur::RequeteEffacerCompte(std::string nickname, std::string password)
{
	//Num�ro de la ligne du compte
	int noCompte;
	if (VerificationCompte(nickname, password))
	{
		//Demande au mod�le d'effacer le compte
		noCompte = modele.NoCompte(nickname);
		modele.EffacerCompte(noCompte);
		return true;
	}
	return false;
}

/// <summary>
/// V�rifie su le compte existe
/// </summary>
/// <param name="nickname">Surnom du joueur</param>
///<return>Retourne true si le compte existe</return>
bool Controleur::CompteExiste(std::string nickname)
{
	bool compteExiste = false;
	//Demande au mod�le tous les noms de compte
	std::vector<std::string> nomCompte = modele.GetNomCompte();
	for (int i = 0; i < nomCompte.size(); i++)
	{
		//V�rifie si le compte existe
		if (nomCompte.at(i) == nickname)
		{
			compteExiste = true;
		}
	}
	return compteExiste;
}

/// <summary>
/// Effectue la v�rification et la modification de compte
/// </summary>
/// <param name="nickname">Surnom du joueur</param>
/// <param name="password">Mot de passe du joueur</param>
/// <param name="nom">Nouveau nom du joueur</param>
/// <param name="prenom">Nouveau pr�nom du joueur</param>
/// <param name="courriel">Nouveau courriel du joueur</param>
///<return>Retourne true si la modification c'est bien d�roul�e</return>
bool Controleur::RequeteModificationCompte(std::string nickname, std::string password, std::string nom, std::string prenom, std::string courriel)
{
	//V�rification des nouvelles donn�es du compte 
	if (ValidationInfoCompte(password, nom, prenom, courriel))
	{
		//Envoie des donn�es au mod�le
		modele.ModifierCompte(nickname, password, nom, prenom, courriel);
		return true;
	}
	return false;
}
