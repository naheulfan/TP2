#pragma once

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Textbox.h"
#include "Modele.h"
#include "Controleur.h"
namespace platformer
{
	class Scores : public Scene
	{
	public:
		Scores();
		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();
	private:
		Textbox scores[10];
		Textbox textbox1;
		Textbox textboxErreur1;
		Textbox textbox2;
		Textbox textboxErreur2;
		Textbox* textboxActif = nullptr;
		Texture ecranTitreT;
		Sprite ecranTitre;
		Font font;
		Text titre;
		Modele modele;
		bool backspaceActif = false;
		bool enterActif = false;
		int topTenScores[10];
	};
}

