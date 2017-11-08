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

	private:
		Controleur();
		static Controleur *instance;
		Modele modele;
		Controleur(const Controleur&);
	};
}