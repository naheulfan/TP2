#include "EffacerCompte.h"
#include "Controleur.h"

using namespace platformer;

EffacerCompte::EffacerCompte()
{

}

EffacerCompte::~EffacerCompte()
{
}

Scene::scenes EffacerCompte::run()
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
bool EffacerCompte::init(RenderWindow * const window)
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

	textboxErreur.initInfo(Vector2f(430, 350), font, true);

	descriptionPassword.initInfo(Vector2f(430, 290), font, false);
	descriptionPassword.insererTexte("Mot de passe");

	textboxNickname.init(480, 25, Vector2f(430, 260), font);

	descriptionNickname.initInfo(Vector2f(430, 230), font, false);
	descriptionNickname.insererTexte("Surnom");

	titre.initInfoTitre(Vector2f(430, 80), font, false);
	titre.insererTexte("Effacer compte");

	this->mainWin = window;
	isRunning = true;
	validation = false;

	return true;
}

/// <summary>
/// Reçoit les évènements du joueur
/// </summary>
void EffacerCompte::getInputs()
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
			else if (textboxNickname.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActif = &textboxNickname; //Ce textbox devient actif
				textboxNickname.selectionner();  //on l'affiche comme étant sélectionné
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


				//Vérification des données
				if (Controleur::GetInstance()->VerificationCompte(textboxNickname.getTexte(), textboxPassword.getTexte()) || validation)
				{
					if (!validation)
					{
						//Garde en mémoire le surnom et le mot de passe
						nickname = textboxNickname.getTexte();
						password = textboxPassword.getTexte();
						textboxNickname.insererTexte("");
					}
					//Validation pour effacer le compte
					descriptionNickname.insererTexte("Entez \"effacer\" pour effacer le compte");
					if (textboxNickname.getTexte() == "effacer")
					{
						//Demande pour effacer le compte
						if (Controleur::GetInstance()->RequeteEffacerCompte(nickname, password))
						{
							//Changement de scène
							isRunning = false;
							transitionVersScene = Controleur::GetInstance()->RequeteChangerScene(Scene::scenes::EFFACER_COMPTE, event);
						}
					}
					else if (validation)
					{
						textboxErreur.insererTexte("Erreur, veillez recommencer");
					}
					validation = true;
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
				textboxActif->retirerChar();
				backspaceActif = true;  //Pour s'assurer que backspace n'est pas saisie comme caractère
			}
			//Changement de scène si la touche "Escape" est appuyée
			else if (event.key.code == Keyboard::Escape)
			{
				isRunning = false;
				transitionVersScene = Controleur::GetInstance()->RequeteChangerScene(Scene::scenes::EFFACER_COMPTE, event);
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
void EffacerCompte::update()
{
	if (textboxActif != &textboxNickname)
	{
		textboxNickname.deSelectionner();
	}
	if (textboxActif != &textboxPassword)
	{
		textboxPassword.deSelectionner();
	}
}

/// <summary>
/// Effectue l'affichage de la scène
/// </summary>
void EffacerCompte::draw()
{
	mainWin->clear();
	mainWin->draw(ecranTitre);
	textboxNickname.dessiner(mainWin);
	descriptionNickname.dessiner(mainWin);
	titre.dessiner(mainWin);
	//Affichage seulement lors de l'étape de validation
	if (!validation)
	{
		descriptionPassword.dessiner(mainWin);
		textboxPassword.dessiner(mainWin);
	}
	textboxErreur.dessiner(mainWin);
	mainWin->display();
}