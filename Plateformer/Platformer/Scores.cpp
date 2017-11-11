#include "Scores.h"


using namespace platformer;
Scores::Scores()
{
}

Scene::scenes Scores::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}
bool Scores::init(RenderWindow * const window)
{
	font.loadFromFile("Ressources\\Fonts\\Peric.ttf");
	for (int i = 0; i < 10; i++)
	{
		scores[i].init(480, 24, sf::Vector2f(mainWin->getSize().x / 2, i * ((mainWin->getSize().y - 200) / 10)),font);
		scores[i].insererTexte("placeholder" + std::to_string(i));
	}
	textbox1.init(480, 24, sf::Vector2f(mainWin->getSize().x, mainWin->getSize().y - 150), font);
	textbox2.init(480, 24, sf::Vector2f(mainWin->getSize().x + 600, mainWin->getSize().y - 150), font);
	textboxErreur1.init(480, 24, sf::Vector2f(mainWin->getSize().x, mainWin->getSize().y - 100), font);
	textboxErreur2.init(480, 24, sf::Vector2f(mainWin->getSize().x + 600, mainWin->getSize().y - 150), font);
}
void Scores::draw()
{
	for (int i = 0; i < 10; i++)
	{
		scores[i].dessiner(mainWin);
	}
}
void Scores::getInputs()
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

			if (textbox1.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActif = &textbox1; //Ce textbox devient actif
				textbox1.selectionner();  //on l'affiche comme étant sélectionné
										  //textboxErreurNickname.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else if (textbox2.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActif = &textbox2; //Ce textbox devient actif
				textbox2.selectionner();  //on l'affiche comme étant sélectionné
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

				if (textboxActif == &textbox1)
				{
					if (Controleur::GetInstance()->CompteExiste(textboxActif->getTexte()))
					{
						int noCompteActif = modele.NoCompte(textboxActif->getTexte());

					}
					else
					{
						//On affiche notre erreur.
						textboxErreur1.insererTexte("Nom invalide, veuillez recommencer");
					}
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
