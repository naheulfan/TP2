#include "ModifierCompte.h"
#include "Controleur.h"

using namespace platformer;

ModifierCompte::ModifierCompte()
{

}

ModifierCompte::~ModifierCompte()
{
}

Scene::scenes ModifierCompte::run()
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
bool ModifierCompte::init(RenderWindow * const window)
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
	textboxNickname.init(480, 25, Vector2f(430, 260), font);
	descriptionNickname.initInfo(Vector2f(430, 230), font, false);
	descriptionNickname.insererTexte("Surnom");

	textboxPassword.init(480, 15, Vector2f(430, 320), font);
	descriptionPassword.initInfo(Vector2f(430, 290), font, false);
	descriptionPassword.insererTexte("Mot de passe");

	textboxNom.init(480, 25, Vector2f(430, 260), font);
	descriptionNom.initInfo(Vector2f(430, 230), font, false);
	descriptionNom.insererTexte("Nom");

	textboxPrenom.init(480, 15, Vector2f(430, 320), font);
	descriptionPrenom.initInfo(Vector2f(430, 290), font, false);
	descriptionPrenom.insererTexte("Prenom");

	textboxCourriel.init(480, 24, Vector2f(430, 380), font);
	descriptionCourriel.initInfo(Vector2f(430, 350), font, false);
	descriptionCourriel.insererTexte("Courriel");

	titre.initInfoTitre(Vector2f(430, 80), font, false);
	titre.insererTexte("Modification compte");

	textboxErreur.initInfo(Vector2f(430, 410), font, true);

	this->mainWin = window;
	isRunning = true;
	validation = false;

	return true;
}

/// <summary>
/// Reçoit les évènements du joueur
/// </summary>
void ModifierCompte::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}

		//Si on a un événement de click de souris
		if (event.type == Event::MouseButtonPressed)
		{
			//Si on touche à la textbox avec la souris
			if (textboxPassword.touche(Mouse::getPosition(*mainWin)) && !validation)
			{
				textboxActif = &textboxPassword; //Ce textbox devient actif
				textboxPassword.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur
			}
			else if (textboxNickname.touche(Mouse::getPosition(*mainWin)) && !validation)
			{
				textboxActif = &textboxNickname; //Ce textbox devient actif
				textboxNickname.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur
			}
			else if (textboxNom.touche(Mouse::getPosition(*mainWin)) && validation)
			{
				textboxActif = &textboxNom; //Ce textbox devient actif
				textboxNom.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur
			}
			else if (textboxPrenom.touche(Mouse::getPosition(*mainWin)) && validation)
			{
				textboxActif = &textboxPrenom; //Ce textbox devient actif
				textboxPrenom.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur
			}

			else if (textboxCourriel.touche(Mouse::getPosition(*mainWin)) && validation)
			{
				textboxActif = &textboxCourriel; //Ce textbox devient actif
				textboxCourriel.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur
			}
			else
			{
				//Sinon aucun textbox actif
				textboxActif = nullptr;
			}
		}

		//Un événement de touche de clavier AVEC un textobx actif
		if (event.type == Event::KeyPressed && textboxActif != nullptr)
		{
			if (event.key.code == Keyboard::Return)
			{
				enterActif = true; //Pour s'assurer que enter n'est pas saisie comme caractère


				if (Controleur::GetInstance()->VerificationCompte(textboxNickname.getTexte(), textboxPassword.getTexte()) || validation)
				{
					//Vérification si les informations entrées sont valide
					if (validation)
					{
						//Modifie le compte
						Controleur::GetInstance()->RequeteModificationCompte(textboxNickname.getTexte(), textboxPassword.getTexte(), textboxNom.getTexte(), textboxPrenom.getTexte(), textboxCourriel.getTexte());
						isRunning = false;
						transitionVersScene = Controleur::GetInstance()->RequeteChangerScene(Scene::scenes::MODIFIER_COMPTE, event);
					}
					validation = true;
				}
				else
				{
					//On affiche notre erreur.
					textboxErreur.insererTexte("Il y a eu une erreur, veillez recommencer");
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
				transitionVersScene = Controleur::GetInstance()->RequeteChangerScene(Scene::scenes::MODIFIER_COMPTE, event);
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
void ModifierCompte::update()
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
void ModifierCompte::draw()
{
	mainWin->clear();
	mainWin->draw(ecranTitre);
	titre.dessiner(mainWin);
	if (!validation)
	{
		textboxNickname.dessiner(mainWin);
		descriptionNickname.dessiner(mainWin);
		descriptionPassword.dessiner(mainWin);
		textboxPassword.dessiner(mainWin);
	}
	if (validation)
	{
		textboxNom.dessiner(mainWin);
		descriptionNom.dessiner(mainWin);
		textboxPrenom.dessiner(mainWin);
		descriptionPrenom.dessiner(mainWin);
		textboxCourriel.dessiner(mainWin);
		descriptionCourriel.dessiner(mainWin);
	}
	textboxErreur.dessiner(mainWin);
	mainWin->display();
}