#include "Modele.h"

using namespace platformer;

Modele::Modele()
{
	nomCompte = {"antoknee", "naheulfan","nobody"};
	passwordCompte = { "anto","zantar", "password" };
}


void Modele::AjoutCompte(std::string nom, std::string password)
{
	nomCompte.push_back(nom);
	passwordCompte.push_back(password);
}

std::string* Modele::DonneeCompte(size_t pos) const
{
	std::string* compte = new std::string[2];
	compte[0] = nomCompte.at(pos);
	compte[1] = passwordCompte.at(pos);
	return compte;
}

size_t Modele::GetSize()
{
	return nomCompte.size();
}

std::vector<std::string> Modele::GetNomCompte()
{
	return nomCompte;
}