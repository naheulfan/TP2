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
		bool VerificationCompte(std::string nom, std::string password);

	private:
		Controleur();
		static Controleur *instance;
		Modele modele;
		Controleur(const Controleur&);
	};
}