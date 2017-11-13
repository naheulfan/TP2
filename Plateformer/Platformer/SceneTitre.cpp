#include "SceneTitre.h"
#include "Controleur.h"
#include "SceneNiveau1.h"
using namespace platformer;

SceneTitre::SceneTitre()
{
	
}

SceneTitre::~SceneTitre()
{
}

Scene::scenes SceneTitre::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}

/// <summary>
/// Initialise les variables de la sc�ne
/// </summary>
/// <param name="window">La fen�tre du jeu</param>
/// <returns>True si l'initialisation c'est bien pass�e</returns>
bool SceneTitre::init(RenderWindow * const window)
{
	//Initialise les textures
	if (!ecranTitreT.loadFromFile("Ressources\\Sprites\\Title.png"))
	{
		return false;
	}

	if (!font.loadFromFile("Ressources\\Fonts\\Peric.ttf"))
	{
		return false;
	}

	ecranTitre.setTexture(ecranTitreT);

	//Initialise les donn�es pour les textbox
	textboxPassword.init(480, 15, Vector2f(430, 320), font);
	descriptionPassword.initInfo(Vector2f(430, 290), font, false);
	descriptionPassword.insererTexte("Mot de passe");

	textboxNickname.init(480, 25, Vector2f(430, 260), font);
	descriptionNickname.initInfo(Vector2f(430, 230), font, false);
	descriptionNickname.insererTexte("Surnom");

	textboxErreur.initInfo(Vector2f(430, 290), font, true);

	this->mainWin = window;
	isRunning = true;
	
	return true;
}

/// <summary>
/// Re�oit les �v�nements du joueur
/// </summary>
void SceneTitre::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		//x sur la fen�tre
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fen�tre ne mettrait pas n�cessairement 
			//fin � l'application
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}

		//Si on a un �v�nement de click de souris
		if (event.type == Event::MouseButtonPressed)
		{
			//Si on touche � la textbox avec la souris
			if (textboxPassword.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActifPassword = &textboxPassword; //Ce textbox devient actif
				textboxPassword.selectionner();  //on l'affiche comme �tant s�lectionn�
				textboxErreur.insererTexte(""); //on efface le message d'erreur (optionnel, amis �a fait clean si on fait un nouvel essai)
			}
			else
			{
				//Sinon aucun textbox actif
				//Ce else devrait �tre dans toutes vos fen�tres o� il n'y a pas de textbox.
				textboxActifPassword = nullptr;
				textboxPassword.deSelectionner();
			}
			//Si on touche � la textbox avec la souris
			if (textboxNickname.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActifPassword = &textboxNickname; //Ce textbox devient actif
				textboxNickname.selectionner();  //on l'affiche comme �tant s�lectionn�
			}
			else
			{
				//Sinon aucun textbox actif
				//Ce else devrait �tre dans toutes vos fen�tres o� il n'y a pas de textbox.
				textboxActifNickname = nullptr;
				textboxNickname.deSelectionner();
			}
		}

		//Un �v�nement de touche de clavier AVEC un textobx actif
		if (event.type == Event::KeyPressed && textboxActifPassword != nullptr)
		{
			//ON VA SE SERVIR DE ENTER PARTOUT DANS LE TP POUR VALIDER LES INFOS DANS TOUS
			//LES TEXTBOX D'UNE SC�NE (Vous pouviez vous codez un bouton si �a vous amuse,
			//Mais vous pouvez aussi garder les choses simples.
			if (event.key.code == Keyboard::Return)
			{
				enterActif = true; //Pour s'assurer que enter n'est pas saisie comme caract�re
				//V�rification si le compte est associ� avec le mot de passe
				if (Controleur::GetInstance()->VerificationCompte(textboxNickname.getTexte(), textboxPassword.getTexte()))
				{
					SceneNiveau1::compteActif = Modele::NoCompte(textboxNickname.getTexte());
					isRunning = false;
					transitionVersScene = Controleur::GetInstance()->RequeteChangerScene(Scene::scenes::TITRE, event);;
				}
				else
				{
					//On affiche notre erreur.
					textboxErreur.insererTexte("Mauvais mot de passe, veillez recommencer");
				}
			}
			//Effacement d'un caract�re dans la textbox active si "Backspace" est appuy�e
			else if (event.key.code == Keyboard::BackSpace)
			{
				textboxActifPassword->retirerChar();
				backspaceActif = true;  //Pour s'assurer que backspace n'est pas saisie comme caract�re
			}
			//Changement de sc�ne si la touche "Escape" est appuy�e
			else if (event.key.code == Keyboard::Escape)
			{
				isRunning = false;
				transitionVersScene = Controleur::GetInstance()->RequeteChangerScene(Scene::scenes::TITRE, event);
			}	
		}

		//Attention : TextEntered est diff�rent de KeyPressed
		//Voir ici pour l'explication: https://www.sfml-dev.org/tutorials/2.4/window-events-fr.php
		if (!backspaceActif && !enterActif && textboxActifPassword != nullptr && (event.type == Event::TextEntered))
		{
			if (event.text.unicode < 128) //Travailler en unicode n'est pas simple en C++; on peut vivre avec du simple
			{                             //ascii pour ce tp (libre � vous d'aller plus loin si vous voulez)
				textboxActifPassword->ajouterChar((char)event.text.unicode);
			}
		}
	}

	//Dans tous les cas on netoie ces conditions apr�s chaque boucle.
	enterActif = false;
	backspaceActif = false;
}

void SceneTitre::update()
{
}

/// <summary>
/// Effectue l'affichage de la sc�ne
/// </summary>
void SceneTitre::draw()
{
	mainWin->clear();
	mainWin->draw(ecranTitre);
	textboxPassword.dessiner(mainWin);
	descriptionPassword.dessiner(mainWin);
	textboxErreur.dessiner(mainWin);
	textboxNickname.dessiner(mainWin);
	descriptionNickname.dessiner(mainWin);
	mainWin->display();
}