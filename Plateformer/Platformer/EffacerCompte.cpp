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
/// Initialise les variables de la sc�ne
/// </summary>
/// <param name="window">La fen�tre du jeu</param>
/// <returns>True si l'initialisation c'est bien pass�e</returns>
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

	//Initialise les donn�es pour les textbox
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
/// Re�oit les �v�nements du joueur
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

		//Si on a un �v�nement de click de souris
		if (event.type == Event::MouseButtonPressed)
		{
			//Si on touche � la textbox avec la souris
			if (textboxPassword.touche(Mouse::getPosition(*mainWin)) && !validation)
			{
				textboxActif = &textboxPassword; //Ce textbox devient actif
				textboxPassword.selectionner();  //on l'affiche comme �tant s�lectionn�
				textboxErreur.insererTexte(""); //on efface le message d'erreur
				
			}
			else if (textboxNickname.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActif = &textboxNickname; //Ce textbox devient actif
				textboxNickname.selectionner();  //on l'affiche comme �tant s�lectionn�
				textboxErreur.insererTexte(""); //on efface le message d'erreur
			}
			else
			{
				//Sinon aucun textbox actif
				textboxActif = nullptr;
			}
		}

		//Un �v�nement de touche de clavier AVEC un textobx actif
		if (event.type == Event::KeyPressed && textboxActif != nullptr)
		{
			if (event.key.code == Keyboard::Return)
			{
				enterActif = true; //Pour s'assurer que enter n'est pas saisie comme caract�re


				//V�rification des donn�es
				if (Controleur::GetInstance()->VerificationCompte(textboxNickname.getTexte(), textboxPassword.getTexte()) || validation)
				{
					if (!validation)
					{
						//Garde en m�moire le surnom et le mot de passe
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
							//Changement de sc�ne
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
			//Effacement d'un caract�re dans la textbox active si "Backspace" est appuy�e
			else if (event.key.code == Keyboard::BackSpace)
			{
				textboxActif->retirerChar();
				backspaceActif = true;  //Pour s'assurer que backspace n'est pas saisie comme caract�re
			}
			//Changement de sc�ne si la touche "Escape" est appuy�e
			else if (event.key.code == Keyboard::Escape)
			{
				isRunning = false;
				transitionVersScene = Controleur::GetInstance()->RequeteChangerScene(Scene::scenes::EFFACER_COMPTE, event);
			}
		}
		//Ajout des caract�res dans la textbox active
		if (!backspaceActif && !enterActif && textboxActif != nullptr && (event.type == Event::TextEntered))
		{
			if (event.text.unicode < 128) 
			{                            
				textboxActif->ajouterChar((char)event.text.unicode);
			}
		}
	}

	//Dans tous les cas on netoie ces conditions apr�s chaque boucle.
	enterActif = false;
	backspaceActif = false;
}

/// <summary>
/// D�selectionne les boites qui ne sont pas actives
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
/// Effectue l'affichage de la sc�ne
/// </summary>
void EffacerCompte::draw()
{
	mainWin->clear();
	mainWin->draw(ecranTitre);
	textboxNickname.dessiner(mainWin);
	descriptionNickname.dessiner(mainWin);
	titre.dessiner(mainWin);
	//Affichage seulement lors de l'�tape de validation
	if (!validation)
	{
		descriptionPassword.dessiner(mainWin);
		textboxPassword.dessiner(mainWin);
	}
	textboxErreur.dessiner(mainWin);
	mainWin->display();
}