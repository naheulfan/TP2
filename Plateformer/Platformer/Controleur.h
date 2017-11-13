#pragma once

#include "Scene.h"
#include "Modele.h"

namespace platformer
{
	class Controleur
	{
	public:
		static Controleur *GetInstance();
		static void Release();

		Scene::scenes RequeteChangerScene(Scene::scenes sceneCourante, Event event);
		bool VerificationCompte(std::string nickname, std::string password);
		bool ValidationCompte(std::string nickname, std::string password, std::string nom, std::string prenom, std::string courriel);
		bool ValidationInfoCompte(std::string password, std::string nom, std::string prenom, std::string courriel);
		bool RequeteEffacerCompte(std::string nickname, std::string password);
		bool CompteExiste(std::string nickname);
		bool RequeteModificationCompte(std::string nickname, std::string password, std::string nom, std::string prenom, std::string courriel);

	private:
		Controleur();
		//Instance du controlleur
		static Controleur *instance;
		Modele modele;
		Controleur(const Controleur&);
	};
}