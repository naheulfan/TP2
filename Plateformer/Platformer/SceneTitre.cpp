#include "SceneTitre.h"
#include "Controleur.h"
#include "Modele.h"
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
/// Initialise les variables de la scène
/// </summary>
/// <param name="window">La fenêtre du jeu</param>
/// <returns>True si l'initialisation c'est bien passée</returns>
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

	//Initialise les données pour les textbox
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
/// Reçoit les évènements du joueur
/// </summary>
void SceneTitre::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fenêtre ne mettrait pas nécessairement 
			//fin à l'application
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}

		//Si on a un événement de click de souris
		if (event.type == Event::MouseButtonPressed)
		{
			//Si on touche à la textbox avec la souris
			if (textboxPassword.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActifPassword = &textboxPassword; //Ce textbox devient actif
				textboxPassword.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else
			{
				//Sinon aucun textbox actif
				//Ce else devrait être dans toutes vos fenêtres où il n'y a pas de textbox.
				textboxActifPassword = nullptr;
				textboxPassword.deSelectionner();
			}
			//Si on touche à la textbox avec la souris
			if (textboxNickname.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActifPassword = &textboxNickname; //Ce textbox devient actif
				textboxNickname.selectionner();  //on l'affiche comme étant sélectionné
			}
			else
			{
				//Sinon aucun textbox actif
				//Ce else devrait être dans toutes vos fenêtres où il n'y a pas de textbox.
				textboxActifNickname = nullptr;
				textboxNickname.deSelectionner();
			}
		}

		//Un événement de touche de clavier AVEC un textobx actif
		if (event.type == Event::KeyPressed && textboxActifPassword != nullptr)
		{
			//ON VA SE SERVIR DE ENTER PARTOUT DANS LE TP POUR VALIDER LES INFOS DANS TOUS
			//LES TEXTBOX D'UNE SCÈNE (Vous pouviez vous codez un bouton si ça vous amuse,
			//Mais vous pouvez aussi garder les choses simples.
			if (event.key.code == Keyboard::Return)
			{
				enterActif = true; //Pour s'assurer que enter n'est pas saisie comme caractère
				//Vérification si le compte est associé avec le mot de passe
				if (Controleur::GetInstance()->VerificationCompte(textboxNickname.getTexte(), textboxPassword.getTexte()))
				{
					//Assigne le numéro du compte
					compteActif = Modele::NoCompte(textboxNickname.getTexte());
					//Changement de scène
					isRunning = false;
					transitionVersScene = Controleur::GetInstance()->RequeteChangerScene(Scene::scenes::TITRE, event);;
				}
				else
				{
					//On affiche notre erreur.
					textboxErreur.insererTexte("Mauvais mot de passe, veillez recommencer");
				}
			}
			//Effacement d'un caractère dans la textbox active si "Backspace" est appuyée
			else if (event.key.code == Keyboard::BackSpace)
			{
				textboxActifPassword->retirerChar();
				backspaceActif = true;  //Pour s'assurer que backspace n'est pas saisie comme caractère
			}
			//Changement de scène si la touche "Escape" est appuyée
			else if (event.key.code == Keyboard::Escape)
			{
				isRunning = false;
				transitionVersScene = Controleur::GetInstance()->RequeteChangerScene(Scene::scenes::TITRE, event);
			}	
		}

		//Attention : TextEntered est différent de KeyPressed
		//Voir ici pour l'explication: https://www.sfml-dev.org/tutorials/2.4/window-events-fr.php
		if (!backspaceActif && !enterActif && textboxActifPassword != nullptr && (event.type == Event::TextEntered))
		{
			if (event.text.unicode < 128) //Travailler en unicode n'est pas simple en C++; on peut vivre avec du simple
			{                             //ascii pour ce tp (libre à vous d'aller plus loin si vous voulez)
				textboxActifPassword->ajouterChar((char)event.text.unicode);
			}
		}
	}

	//Dans tous les cas on netoie ces conditions après chaque boucle.
	enterActif = false;
	backspaceActif = false;
}

void SceneTitre::update()
{
}

/// <summary>
/// Effectue l'affichage de la scène
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