#pragma once

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Textbox.h"
#include "Modele.h"

namespace platformer
{
	class CreationCompte : public Scene
	{
	public:
		CreationCompte();
		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();
	private:
		Textbox textbox;
		Textbox textboxErreur;
		Textbox* textboxActif = nullptr;
		Texture ecranTitreT;
		Sprite ecranTitre;
		Font font;
		Text titre;
		Modele modele;

		bool backspaceActif = false;
		bool enterActif = false;
	};
}
