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

	//textboxNickname.init(480, 24, Vector2f(430, 260), font);

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
		if (event.type == Event::KeyPressed && textboxActif != nullptr)
		{
			//VALIDER LES INFOS DANS TOUS LES TEXTBOX D'UNE SCÈNE
			if (event.key.code == Keyboard::Return)
			{
				enterActif = true; //Pour s'assurer que enter n'est pas saisie comme caractère

				//Appeller ajout compte
				if (Controleur::GetInstance()->ValidationCompte("naheulfanv", "Bruno-123", "Pleau", "Bruno" , "bruno@gmail.com"))
				{
					modele.AjoutCompte("naheulfanv", "Bruno-123", "Pleau", "Bruno", "bruno@gmail.com");
				}
				else
				{
					//On affiche notre erreur.
					textboxErreur.insererTexte("Mauvais mot de passe, veillez recommencer");
				}
			}
			else if (event.key.code == Keyboard::BackSpace)
			{
				textboxActif->retirerChar();
				backspaceActif = true;  //Pour s'assurer que backspace n'est pas saisie comme caractère
			}
			else if (event.key.code == Keyboard::Escape)
			{
				isRunning = false;
				transitionVersScene = Controleur::GetInstance()->RequeteChangerScene(Scene::scenes::CREER_COMPTE, event);
			}
		}
		if (!backspaceActif && !enterActif && textboxActif != nullptr && (event.type == Event::TextEntered))
		{
			if (event.text.unicode < 128) 
			{                            
				textboxActif->ajouterChar((char)event.text.unicode);
			}
		}
	}
	enterActif = false;
	backspaceActif = false;
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