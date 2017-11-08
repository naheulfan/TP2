#include "Modele.h"
#include <fstream>

using namespace platformer;

Modele::Modele()
{
	nicknameCompte = {"antoknee", "naheulfan","nobody"};
	passwordCompte = { "anto","zantar", "password" };
	//Voir si ça marche et si seulement l'initier dans la méthode
	//fichier = std::fstream("compte.txt");
}


void Modele::AjoutCompte(std::string nickname, std::string password, std::string nom, std::string prenom, std::string courriel)
{
	//std::ofstream fichier("compte.txt");
	//instruction pour écrire dans le txt...

	//À changer, ajouter les infos dans le fichier .txt
	nicknameCompte.push_back(nickname);
	passwordCompte.push_back(password);
	nomCompte.push_back(nom);
	prenomCompte.push_back(prenom);
	courrielCompte.push_back(courriel);
}

std::string* Modele::DonneeCompte(size_t pos) const
{
	//std::ifstream fichier("compte.txt");
	//string line;
	//while (getline(fichier, line))
	//voir exemple algo...

	//À changer
	std::string* compte = new std::string[2];
	compte[0] = nicknameCompte.at(pos);
	compte[1] = passwordCompte.at(pos);
	return compte;
}

size_t Modele::GetSize()
{
	return nicknameCompte.size();
}

std::vector<std::string> Modele::GetNomCompte()
{
	return nicknameCompte;
}