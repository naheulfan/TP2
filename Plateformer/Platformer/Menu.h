#pragma once

#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Textbox.h"

namespace platformer
{
	class SceneMenu : public Scene
	{
	public:
		SceneMenu();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();
	private:
		Texture ecranTitreT;
		Sprite ecranTitre;
		Font font;
		Textbox texteLogin;
		Textbox texteScore;
		Textbox texteCompte;
	};
}