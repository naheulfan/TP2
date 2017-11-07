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
		
		std::string* DonneeCompte(size_t pos) const;

		size_t GetSize();

		std::vector<std::string> GetNomCompte();

	private:
		std::vector<std::string> nicknameCompte;
		std::vector<std::string> passwordCompte;
		std::vector<std::string> nomCompte;
		std::vector<std::string> prenomCompte;
		std::vector<std::string> courrielCompte;
	};
}