#include "CreationCompte.h"
#include "Controleur.h"

using namespace platformer;

CreationCompte::CreationCompte()
{
}

Scene::scenes CreationCompte::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}

bool CreationCompte::init(RenderWindow * const window)
{
	if (!font.loadFromFile("Ressources\\Fonts\\Peric.ttf"))
	{
		return false;
	}

	textbox.init(480, 24, Vector2f(430, 320), font);

	titre.setString("Creation compte");
	titre.setFont(font);
	titre.setCharacterSize(50);
	titre.setFillColor(Color::White);

	this->mainWin = window;
	isRunning = true;

	return true;
}

void CreationCompte::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}

		transitionVersScene = Controleur::GetInstance()->RequeteChangerScene(Scene::scenes::GESTION_COMPTE, event);
		if (transitionVersScene != Scene::scenes::GESTION_COMPTE)
		{
			isRunning = false;
		}

		if (event.type == Event::MouseButtonPressed)
		{
			//Si on touche à la textbox avec la souris
			if (textbox.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActif = &textbox; //Ce textbox devient actif
				textbox.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else
			{
				//Sinon aucun textbox actif
				//Ce else devrait être dans toutes vos fenêtres où il n'y a pas de textbox.
				textboxActif = nullptr;
				textbox.deSelectionner();
			}

		}
	}
}

void CreationCompte::update()
{
	titre.setPosition(mainWin->getSize().x / 2 - 175, 80);

}

void CreationCompte::draw()
{
	mainWin->clear();
	mainWin->draw(titre);
	textbox.dessiner(mainWin);
	mainWin->display();

}