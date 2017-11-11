#include "Modele.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace platformer;

Modele::Modele()
{
}


void Modele::AjoutCompte(std::string nickname, std::string password, std::string nom, std::string prenom, std::string courriel)
{
	//Ajouter vérification si fichier ouvert, etc.
	std::ofstream fichier("comptes.txt", std::ofstream::app);
	fichier << nickname << " " << password << " " << nom << " " << prenom << " " << courriel << std::endl;
	fichier.close();
}

std::string* Modele::DonneeCompte(std::string nickname) const
{
	std::ifstream fichier("comptes.txt");
	std::string line;
	std::string* compte = new std::string[6];
	int noCompte = 0;
	while (getline(fichier, line))
	{
		std::stringstream l(line);
		std::string surnom, password, nom, prenom, courriel;
		l >> surnom >> password >> nom >> prenom >> courriel;
		if (surnom == nickname)
		{
			compte[0] = surnom;
			compte[1] = password;
			compte[2] = nom;
			compte[3] = prenom;
			compte[4] = courriel;
			compte[5] = noCompte;
		}
		++noCompte;
	}
	fichier.close();
	return compte;
}

std::vector<std::string> Modele::GetNomCompte() const
{
	std::vector<std::string> nomComptes;
	std::ifstream fichier("comptes.txt");
	std::string line;
	while (getline(fichier, line))
	{
		std::stringstream l(line);
		std::string nickname;
		l >> nickname;
		nomComptes.push_back(nickname);
	}
	fichier.close();
	return nomComptes;
}

void Modele::EffacerCompte(int noLigneEffacer)
{
	std::string texte = "";
	std::ifstream fichier("comptes.txt");
	if (fichier)
	{
		std::string line;
		int compteurLine = 0;
		while (getline(fichier, line))
		{
			++compteurLine;
			if (compteurLine != noLigneEffacer)
			{
				texte += line + "\n";
			}
		}
	}
	fichier.close();

	std::ofstream nouveauFichier("comptes.txt");
	nouveauFichier << texte;
	nouveauFichier.close();

	//Effacer scores du compte
}