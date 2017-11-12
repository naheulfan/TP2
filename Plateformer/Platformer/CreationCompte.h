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
		Texture ecranTitreT;
		Sprite ecranTitre;

		Textbox textboxNickname;
		Textbox descriptionNickname;

		Textbox textboxPassword;
		Textbox descriptionPassword;
		Textbox infoPassword;
		Textbox infoPassword2;

		Textbox textboxNom;
		Textbox descriptionNom;

		Textbox textboxPrenom;
		Textbox descriptionPrenom;

		Textbox textboxCourriel;
		Textbox descriptionCourriel;

		Textbox textboxErreur;

		Textbox* textboxActif = nullptr;

		Textbox titre;

		Font font;
		Modele modele;

		bool backspaceActif = false;
		bool enterActif = false;
	};
}
