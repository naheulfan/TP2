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
		Textbox textbox3;
		Textbox textboxErreur3;

		Textbox textbox2;
		Textbox textboxErreur2;

		Textbox textbox;
		Textbox textboxErreur;

		Textbox textbox1;
		Textbox textboxErreur1;

		Textbox textbox0;
		Textbox textboxErreur0;

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
