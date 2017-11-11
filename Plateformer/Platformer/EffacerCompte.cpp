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

bool EffacerCompte::init(RenderWindow * const window)
{
	if (!ecranTitreT.loadFromFile("Ressources\\Sprites\\Title.png"))
	{
		return false;
	}

	if (!font.loadFromFile("Ressources\\Fonts\\Peric.ttf"))
	{
		return false;
	}

	ecranTitre.setTexture(ecranTitreT);

	//Les positions sont arbitraires, obtenus par essai et erreur.
	//par rapport au fond d'écran
	textboxPassword.init(480, 24, Vector2f(430, 320), font);

	textboxErreur.initInfo(Vector2f(430, 350), font, true);

	descriptionPassword.initInfo(Vector2f(430, 290), font, false);
	descriptionPassword.insererTexte("Mot de passe");

	textboxNickname.init(480, 24, Vector2f(430, 260), font);

	descriptionNickname.initInfo(Vector2f(430, 230), font, false);
	descriptionNickname.insererTexte("Surnom");

	this->mainWin = window;
	isRunning = true;
	validation = false;

	return true;
}

void EffacerCompte::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		//Esseyer de mettre dans controlleur
		if (event.type == Event::Closed)
		{
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}

		//Si on a un événement de click de souris
		if (event.type == Event::MouseButtonPressed)
		{
			//Si on touche à la textbox avec la souris
			if (textboxPassword.touche(Mouse::getPosition(*mainWin)) && validation == false)
			{
				textboxActif = &textboxPassword; //Ce textbox devient actif
				textboxPassword.selectionner();  //on l'affiche comme étant sélectionné
				textboxErreur.insererTexte(""); //on efface le message d'erreur
				
			}
			//Sinon on touche l'autre textbox avec la souris
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


				if (Controleur::GetInstance()->VerificationCompte(textboxNickname.getTexte(), textboxPassword.getTexte()) || validation == true)
				{
					//Ajouter une deuxième vérification
					if (validation == false)
					{
						nickname = textboxNickname.getTexte();
						password = textboxPassword.getTexte();
						textboxNickname.insererTexte("");
					}
					descriptionNickname.insererTexte("Entez \"effacer\" pour effacer le compte");
					if (textboxNickname.getTexte() == "effacer")
					{
						Controleur::GetInstance()->RequeteEffacerCompte(nickname, password);
						//À changer
						isRunning = false;
						transitionVersScene = Scene::scenes::MENU;
					}
					else if (validation == true)
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
			else if (event.key.code == Keyboard::BackSpace)
			{
				textboxActif->retirerChar();
				backspaceActif = true;  //Pour s'assurer que backspace n'est pas saisie comme caractère
			}
			else if (event.key.code == Keyboard::Escape)
			{
				isRunning = false;
				transitionVersScene = Controleur::GetInstance()->RequeteChangerScene(Scene::scenes::TITRE, event);
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

	//Dans tous les cas on netoie ces conditions après chaque boucle.
	enterActif = false;
	backspaceActif = false;
}

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

void EffacerCompte::draw()
{
	mainWin->clear();
	mainWin->draw(ecranTitre);
	textboxNickname.dessiner(mainWin);
	descriptionNickname.dessiner(mainWin);
	if (validation == false)
	{
		descriptionPassword.dessiner(mainWin);
		textboxPassword.dessiner(mainWin);
	}
	textboxErreur.dessiner(mainWin);
	mainWin->display();
}