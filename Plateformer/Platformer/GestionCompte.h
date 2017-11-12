#pragma once

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Textbox.h"

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
		Texture ecranTitreT;
		Sprite ecranTitre;
		Font font;
		Textbox titre;
		Textbox texteModifier;
		Textbox texteEffacer;
		Textbox texteCreer;
		Textbox texteMenu;
	};
}