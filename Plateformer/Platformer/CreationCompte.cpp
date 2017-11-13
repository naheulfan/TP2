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

/// <summary>
/// Initialise les variables de la scène
/// </summary>
/// <param name="window">La fenêtre du jeu</param>
/// <returns>True si l'initialisation c'est bien passée</returns>
bool CreationCompte::init(RenderWindow * const window)
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
	textboxNickname.init(480, 25, Vector2f(430, 180), font);
	descriptionNickname.initInfo(Vector2f(430, 150), font, false);
	descriptionNickname.insererTexte("Surnom");

	textboxPassword.init(480, 15, Vector2f(430, 240), font);
	descriptionPassword.initInfo(Vector2f(430, 210), font, false);
	descriptionPassword.insererTexte("*Mot de passe");
	infoPassword.initInfo(Vector2f(430, 450), font, true);
	infoPassword.insererTexte("*Une lette minuscule, une lettre majuscule,");
	infoPassword2.initInfo(Vector2f(430, 465), font, true);
	infoPassword2.insererTexte("un chiffre et un caractere special");

	textboxNom.init(480, 25, Vector2f(430, 300), font);
	descriptionNom.initInfo(Vector2f(430, 270), font, false);
	descriptionNom.insererTexte("Nom");

	textboxPrenom.init(480, 25, Vector2f(430, 360), font);
	descriptionPrenom.initInfo(Vector2f(430, 330), font, false);
	descriptionPrenom.insererTexte("Prenom");

	textboxCourriel.init(480, 24, Vector2f(430, 420), font);
	descriptionCourriel.initInfo(Vector2f(430, 390), font, false);
	descriptionCourriel.insererTexte("Courriel");

	titre.initInfoTitre(Vector2f(430, 80), font, false);
	titre.insererTexte("Creation compte");

	textboxErreur.initInfo(Vector2f(430, 110), font, true);

	this->mainWin = window;
	isRunning = true;

	return true;
}

/// <summary>
/// Reçoit les évènements du joueur
/// </summary>
void CreationCompte::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}

		//Si on a un événement de click de souris
		else if (event.type == Event::MouseButtonPressed)
		{
			//Si on touche à la textbox avec la souris
			if (textboxNickname.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActif = &textboxNickname; //Ce textbox devient actif
				textboxNickname.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte("");	 //textboxErreurNickname.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else if (textboxPassword.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActif = &textboxPassword; //Ce textbox devient actif
				textboxPassword.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte("");	//textboxErreurNickname.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else if (textboxNom.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActif = &textboxNom; //Ce textbox devient actif
				textboxNom.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else if (textboxPrenom.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActif = &textboxPrenom; //Ce textbox devient actif
				textboxPrenom.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else if (textboxCourriel.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActif = &textboxCourriel; //Ce textbox devient actif
				textboxCourriel.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else
			{
				//Sinon aucun textbox actif
				//Ce else devrait être dans toutes vos fenêtres où il n'y a pas de textbox.
				textboxActif = nullptr;
			}


		}	
		//Un événement de touche de clavier AVEC un textobx actif
		if (event.type == Event::KeyPressed && textboxActif != nullptr)
		{
			if (event.key.code == Keyboard::Return)
			{
				enterActif = true; //Pour s'assurer que enter n'est pas saisie comme caractère

				//Vérification des données
				if (Controleur::GetInstance()->ValidationCompte(textboxNickname.getTexte(), textboxPassword.getTexte(), textboxNom.getTexte(), textboxPrenom.getTexte(), textboxCourriel.getTexte()))
				{
					//Ajout du compte
					modele.AjoutCompte(textboxNickname.getTexte(), textboxPassword.getTexte(), textboxNom.getTexte(), textboxPrenom.getTexte(), textboxCourriel.getTexte());
					//Changement de scène
					isRunning = false;
					transitionVersScene = Controleur::GetInstance()->RequeteChangerScene(Scene::scenes::CREER_COMPTE, event);
				}
				else
				{
					//On affiche notre erreur.
					textboxErreur.insererTexte("Erreur, veillez recommencer");
				}
			}
			//Effacement d'un caractère dans la textbox active si "Backspace" est appuyée
			else if (event.key.code == Keyboard::BackSpace)
			{
				textboxActif->retirerChar();
				backspaceActif = true;  //Pour s'assurer que backspace n'est pas saisie comme caractère
			}
			//Changement de scène si la touche "Escape" est appuyée
			else if (event.key.code == Keyboard::Escape)
			{
				isRunning = false;
				transitionVersScene = Controleur::GetInstance()->RequeteChangerScene(Scene::scenes::CREER_COMPTE, event);
			}
		}
		//Ajout des caractères dans la textbox active
		if (!backspaceActif && !enterActif && textboxActif != nullptr && (event.type == Event::TextEntered))
		{
			if (event.text.unicode < 128) 
			{                            
				textboxActif->ajouterChar((char)event.text.unicode);
			}
		}
	}
	//Dans tous les cas on netoie ces conditions après chaque boucle.
	enterActif = false;
	backspaceActif = false;
}

/// <summary>
/// Déselectionne les boites qui ne sont pas actives
/// </summary>
void CreationCompte::update()
{
	if (textboxActif != &textboxNickname)
	{
		textboxNickname.deSelectionner();
	}
	if (textboxActif != &textboxPassword)
	{
		textboxPassword.deSelectionner();
	}
	if (textboxActif != &textboxNom)
	{
		textboxNom.deSelectionner();
	}
	if (textboxActif != &textboxPrenom)
	{
		textboxPrenom.deSelectionner();
	}
	if (textboxActif != &textboxCourriel)
	{
		textboxCourriel.deSelectionner();
	}
}

/// <summary>
/// Effectue l'affichage de la scène
/// </summary>
void CreationCompte::draw()
{
	mainWin->clear();
	mainWin->draw(ecranTitre);
	titre.dessiner(mainWin);
	textboxNickname.dessiner(mainWin);
	descriptionNickname.dessiner(mainWin);
	textboxPassword.dessiner(mainWin);
	descriptionPassword.dessiner(mainWin);
	infoPassword.dessiner(mainWin);
	infoPassword2.dessiner(mainWin);
	textboxNom.dessiner(mainWin);
	descriptionNom.dessiner(mainWin);
	textboxPrenom.dessiner(mainWin);
	descriptionPrenom.dessiner(mainWin);
	textboxCourriel.dessiner(mainWin);
	descriptionCourriel.dessiner(mainWin);
	mainWin->display();

}