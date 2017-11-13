#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Textbox.h"


namespace platformer
{
	class EffacerCompte : public Scene
	{
	public:
		EffacerCompte();
		~EffacerCompte();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();

	private:
		//L'�cran titre est super arbitraire, vous pouvez en trouver un autre si vous voulez.
		Texture ecranTitreT;
		Sprite ecranTitre;

		//Surnom et mot de passe du compte � effacer
		std::string nickname;
		std::string password;

		//Boites de texte
		Textbox textboxNickname;
		Textbox textboxPassword;
		//Message d'erreur
		Textbox textboxErreur; 

		//Message
		Textbox descriptionNickname;
		Textbox descriptionPassword;
		Textbox titre;

		Textbox* textboxActif = nullptr;

		Font font;

		//N�cessaire car on ne peut pas que le code ascii que Enter et Backspace ne soit jamais saisie
		bool backspaceActif = false;
		bool enterActif = false;

		//True si on est rendu � la v�rificaiton
		bool validation;
	};
}