#pragma once

#include "Scene.h"

namespace platformer
{
	class Controleur
	{
	public:
		static Controleur *GetInstance();
		static void Release();

		Scene::scenes RequeteChangerScene(Scene::scenes sceneCourante, Event event);

	private:
		Controleur();
		static Controleur *instance;

		Controleur(const Controleur&);
	};
}