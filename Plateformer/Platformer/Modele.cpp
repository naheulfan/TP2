#include "Modele.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace platformer;

Modele::Modele()
{
}
 int Modele::noCompte;
/// <summary>
/// Ajout d'un compte dans le fichier .txt
/// </summary>
/// <param name="nickname">Surnom du joueur</param>
/// <param name="password">Mot de passe du joueur</param>
/// <param name="nom">Nom du joueur</param>
/// <param name="prenom">Prénom du joueur</param>
/// <param name="courriel">Courriel du joueur</param>
void Modele::AjoutCompte(std::string nickname, std::string password, std::string nom, std::string prenom, std::string courriel)
{
	std::ofstream fichier("comptes.txt", std::ofstream::app);
	if (fichier)
	{
		//Ajoute les informations du compte dans le fichier
		fichier << nickname << " " << password << " " << nom << " " << prenom << " " << courriel << std::endl;
	}
	fichier.close();
}

/// <summary>
/// Donne les données d'un compte
/// </summary>
/// <param name="nickname">Surnom du joueur</param>
/// <returns>Retourne les données du compte dans un tableau de string</returns>
std::string* Modele::DonneeCompte(std::string nickname) const
{
	std::ifstream fichier("comptes.txt");
	std::string line;
	//Données du compte
	std::string* compte = new std::string[5];
	while (getline(fichier, line))
	{
		std::stringstream l(line);
		std::string surnom, password, nom, prenom, courriel;
		l >> surnom >> password >> nom >> prenom >> courriel;
		//Ajout des valeurs dans le tableau
		if (surnom == nickname)
		{
			compte[0] = surnom;
			compte[1] = password;
			compte[2] = nom;
			compte[3] = prenom;
			compte[4] = courriel;
		}
	}
	fichier.close();
	return compte;
}

/// <summary>
/// Donne les noms des comptes
/// </summary>
/// <returns>Retourne un vecteur avec les noms des comptes</returns>
std::vector<std::string> Modele::GetNomCompte() const
{
	std::vector<std::string> nomComptes;
	std::ifstream fichier("comptes.txt");
	std::string line;
	while (getline(fichier, line))
	{
		//Ajout des noms dans le vecteur
		std::stringstream l(line);
		std::string nickname;
		l >> nickname;
		nomComptes.push_back(nickname);
	}
	fichier.close();
	return nomComptes;
}

/// <summary>
/// Donne les scores d'un compte
/// </summary>
/// <returns>Retourne les scores d'un compte</returns>
std::vector<std::string> Modele::GetScoresCompte() const
{
	std::vector<std::string> scores;
	std::ifstream fichier("scores.txt");
	std::string line;
	while (getline(fichier, line))
	{
		//Ajout du score dans le vecteur
		scores.push_back(line);
	}
	fichier.close();
	return scores;
}

/// <summary>
/// Efface un compte du fichier .txt
/// </summary>
/// <param name="noLigneEffacer">Le numéro de la ligne du compte</param>
void Modele::EffacerCompte(int noLigneEffacer)
{
	//Le contenu du fichier
	std::string texte = "";
	std::ifstream fichier("comptes.txt");
	if (fichier)
	{
		std::string line;
		int compteurLine = 0;
		while (getline(fichier, line))
		{
			//Effacement du compte dans la string
			++compteurLine;
			if (compteurLine != noLigneEffacer)
			{
				texte += line + "\n";
			}
		}
	}
	fichier.close();
	//On ajoute le texte dans le fichier
	std::ofstream nouveauFichier("comptes.txt");
	nouveauFichier << texte;
	nouveauFichier.close();

	//Effacer scores du compte
}

/// <summary>
/// Donne le numéro d'un compte
/// </summary>
/// <param name="nickname">Surnom du joueur</param>
/// <returns>Retourne le numéro du compte</returns>
int Modele::NoCompte(std::string nickname)
{
	std::ifstream fichier("comptes.txt");

		std::string line;
		bool compteTrouver = false;
		int noCompte = 0;
		if (fichier)
		{
			while (getline(fichier, line) && compteTrouver == false)
			{
				std::stringstream l(line);
				std::string surnom;
				l >> surnom;
				//Si on est a la ligne du compte
				if (surnom == nickname)
				{
					compteTrouver = true;
				}
				++noCompte;
			}
		}
	fichier.close();
	return noCompte;
}

/// <summary>
/// Modifie les informations d'un compte
/// </summary>
/// <param name="nickname">Surnom du joueur</param>
/// <param name="password">Mot de passe du joueur</param>
/// <param name="nom">Nom du joueur</param>
/// <param name="prenom">Prénom du joueur</param>
/// <param name="courriel">Courriel du joueur</param>
void Modele::ModifierCompte(std::string nickname, std::string password, std::string nom, std::string prenom, std::string courriel)
{
	//Le contenu du fichier
	std::string texte = "";
	std::ifstream fichier("comptes.txt");
	if (fichier)
	{
		std::string line;
		int compteurLine = 0;
		while (getline(fichier, line))
		{
			++compteurLine;
			//On recopie la ligne des autres comptes
			if (compteurLine != NoCompte(nickname))
			{
				texte += line + "\n";
			}
			else
			{
				//On ajoute la ligne modifiée du compte
				texte += nickname + " " + password + " " + nom + " " + prenom + " " + courriel + "\n";
			}
		}
	}
	fichier.close();

	//Ajoute la string dans le texte
	std::ofstream nouveauFichier("comptes.txt");
	nouveauFichier << texte;
	nouveauFichier.close();
}
void Modele::setNoCompte(int noCompte)
{
	Modele::noCompte = noCompte;
}
int Modele::GetNoCompte()
{
	return Modele::noCompte;
}