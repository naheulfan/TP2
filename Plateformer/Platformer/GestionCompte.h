#pragma once

#include <SFML/Graphics.hpp>
#include "Scene.h"

namespace platformer
{
	class GestionCompte : public Scene
	{
	public:
		GestionCompte();
		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();
	private:
		//Texture ecranTitreT;
		//Sprite ecranTitre;
		Font font;
		Text titre;
		Text texteModifier;
		Text texteEffacer;
		Text texteCreer;
		Text texteMenu;
	};
}