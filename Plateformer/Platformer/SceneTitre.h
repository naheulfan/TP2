#pragma once
//class SceneTitre
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Textbox.h"


using namespace sf;

namespace platformer
{
	class SceneTitre: public Scene
	{
	public:
		SceneTitre();
		~SceneTitre();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();

	private:
		//L'�cran titre est super arbitraire, vous pouvez en trouver un autre si vous voulez.
		Texture ecranTitreT;
		Sprite ecranTitre;

		//Boite de texte
		Textbox textboxPassword;
		Textbox textboxNickname;

		//Message
		Textbox descriptionPassword;
		Textbox descriptionNickname;

		//Message d'erreur
		Textbox textboxErreur; 

		

		Font font;

		//N�cessaire car on ne peut pas que le code ascii que Enter et Backspace ne soit jamais saisie
		bool backspaceActif = false;
		bool enterActif = false;
		
		//Ne fait pas beaucoup sens � un Textbox, mais � plusieurs, �a le fera.
		Textbox* textboxActifPassword = nullptr;	
		Textbox* textboxActifNickname = nullptr;
	};
}
