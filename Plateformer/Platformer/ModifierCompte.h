#pragma once
#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.h"
#include "Textbox.h"


namespace platformer
{
	class ModifierCompte : public Scene
	{
	public:
		ModifierCompte();
		~ModifierCompte();

		scenes run();
		bool init(RenderWindow * const window);
		void getInputs();
		void update();
		void draw();

	private:
		//L'écran titre est super arbitraire, vous pouvez en trouver un autre si vous voulez.
		Texture ecranTitreT;
		Sprite ecranTitre;

		//Surnom et mot de passe du compte à effacer
		std::string nickname;
		std::string password;

		//Boites de texte
		Textbox textboxNickname;
		Textbox textboxPassword;
		Textbox textboxNom;
		Textbox textboxPrenom;
		Textbox textboxCourriel;
		//Message d'erreur
		Textbox textboxErreur;

		//Message
		Textbox descriptionNickname;
		Textbox descriptionPassword;
		Textbox descriptionNom;
		Textbox descriptionPrenom;
		Textbox descriptionCourriel;

		Textbox* textboxActif = nullptr;

		Font font;

		//Nécessaire car on ne peut pas que le code ascii que Enter et Backspace ne soit jamais saisie
		bool backspaceActif = false;
		bool enterActif = false;

		bool validation;
	};
}