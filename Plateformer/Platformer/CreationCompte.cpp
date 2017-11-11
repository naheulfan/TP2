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
	textbox3.init(480, 24, Vector2f(430, 200), font);
	textboxErreur3.initInfo(Vector2f(430, 170), font, true);

	textbox2.init(480, 24, Vector2f(430, 260), font);
	textboxErreur2.initInfo(Vector2f(430, 230), font, true);

	textbox.init(480, 24, Vector2f(430, 320), font);
	textboxErreur.initInfo(Vector2f(430, 290), font, true);

	textbox1.init(480, 24, Vector2f(430, 380), font);
	textboxErreur1.initInfo(Vector2f(430, 350), font, true);

	textbox0.init(480, 24, Vector2f(430, 440), font);
	textboxErreur0.initInfo(Vector2f(430, 410), font, true);

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


		else if (event.type == Event::MouseButtonPressed)
		{
			//Si on touche à la textbox avec la souris
			if (textbox3.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActif = &textbox3; //Ce textbox devient actif
				textbox3.selectionner();  //on l'affiche comme étant sélectionné
										  //textboxErreurNickname.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else if (textbox2.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActif = &textbox2; //Ce textbox devient actif
				textbox2.selectionner();  //on l'affiche comme étant sélectionné
										  //textboxErreurNickname.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else if (textbox.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActif = &textbox; //Ce textbox devient actif
				textbox.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else if (textbox1.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActif = &textbox1; //Ce textbox devient actif
				textbox1.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur1.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else if (textbox0.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActif = &textbox0; //Ce textbox devient actif
				textbox0.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur0.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else
			{
				//Sinon aucun textbox actif
				//Ce else devrait être dans toutes vos fenêtres où il n'y a pas de textbox.
				textboxActif = nullptr;
			}


		}
		if (event.type == Event::KeyPressed && textboxActif != nullptr)
		{
			//VALIDER LES INFOS DANS TOUS LES TEXTBOX D'UNE SCÈNE
			if (event.key.code == Keyboard::Return)
			{
				enterActif = true; //Pour s'assurer que enter n'est pas saisie comme caractère

				//Appeller ajout compte
				if (Controleur::GetInstance()->ValidationCompte(textbox3.getTexte(), textbox2.getTexte(), textbox.getTexte(), textbox1.getTexte(), textbox0.getTexte()))
				{
					modele.AjoutCompte(textbox3.getTexte(), textbox2.getTexte(), textbox.getTexte(), textbox1.getTexte(), textbox0.getTexte());
					isRunning = false;
					transitionVersScene = Controleur::GetInstance()->RequeteChangerScene(Scene::scenes::CREER_COMPTE, event);
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
	if (textboxActif != &textbox3)
	{
		textbox3.deSelectionner();
	}
	if (textboxActif != &textbox2)
	{
		textbox2.deSelectionner();
	}
	if (textboxActif != &textbox)
	{
		textbox.deSelectionner();
	}
	if (textboxActif != &textbox1)
	{
		textbox1.deSelectionner();
	}
	if (textboxActif != &textbox0)
	{
		textbox0.deSelectionner();
	}
}

void CreationCompte::draw()
{
	mainWin->clear();
	mainWin->draw(titre);
	textbox3.dessiner(mainWin);
	textbox2.dessiner(mainWin);
	textbox.dessiner(mainWin);
	textbox1.dessiner(mainWin);
	textbox0.dessiner(mainWin);
	mainWin->display();

}