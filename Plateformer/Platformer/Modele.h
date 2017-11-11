#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

namespace platformer
{
	class Modele
	{
	public:
		Modele();
		void AjoutCompte(std::string nickname, std::string password, std::string nom, std::string prenom, std::string courriel);
		
		std::string* DonneeCompte(std::string nickname) const;

		std::vector<std::string> GetNomCompte() const;

		void EffacerCompte(int noLigneEffacer);

		int NoCompte(std::string nickname);

		void ModifierCompte(std::string nickname, std::string password, std::string nom, std::string prenom, std::string courriel);
	private:
		//poid mouche ?
	};
}