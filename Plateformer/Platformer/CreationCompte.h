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
		Textbox textboxNickname;
		Textbox textboxErreur3;

		Textbox textboxPassword;
		Textbox textboxErreur2;

		Textbox textboxNom;
		Textbox textboxErreur;

		Textbox textboxPrenom;
		Textbox textboxErreur1;

		Textbox textboxCourriel;
		Textbox textboxErreur0;

		Textbox* textboxActif = nullptr;

		Textbox titre;

		Texture ecranTitreT;
		Sprite ecranTitre;
		Font font;
		Modele modele;

		bool backspaceActif = false;
		bool enterActif = false;
	};
}
