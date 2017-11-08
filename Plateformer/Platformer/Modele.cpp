#include "Modele.h"

using namespace platformer;

Modele::Modele()
{
	nicknameCompte = {"antoknee", "naheulfan","nobody"};
	passwordCompte = { "anto","zantar", "password" };
}


void Modele::AjoutCompte(std::string nickname, std::string password, std::string nom, std::string prenom, std::string courriel)
{
	nicknameCompte.push_back(nickname);
	passwordCompte.push_back(password);
	nomCompte.push_back(nom);
	prenomCompte.push_back(prenom);
	courrielCompte.push_back(courriel);
}

std::string* Modele::DonneeCompte(size_t pos) const
{
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