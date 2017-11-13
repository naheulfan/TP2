#include "Menu.h"
#include "Controleur.h"

using namespace platformer;

SceneMenu::SceneMenu()
{
}

Scene::scenes SceneMenu::run()
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
bool SceneMenu::init(RenderWindow * const window)
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
	//Initialise les données pour les textbox
	texteLogin.initInfo(Vector2f(430, 350), font, false);
	texteLogin.insererTexte("Espace pour continuer");

	texteScore.initInfo(Vector2f(430, 320), font, false);
	texteScore.insererTexte("\"S\" pour les scores");

	texteCompte.initInfo(Vector2f(430, 290), font, false);
	texteCompte.insererTexte("\"G\" pour la gestion de compte");
	
	ecranTitre.setTexture(ecranTitreT);

	this->mainWin = window;
	isRunning = true;
	
	return true;
}

/// <summary>
/// Reçoit les évènements du joueur
/// </summary>
void SceneMenu::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			//Changement de scène
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}
		//Changement de scène
		transitionVersScene = Controleur::GetInstance()->RequeteChangerScene(Scene::scenes::MENU, event);
		if (transitionVersScene != Scene::scenes::MENU)
		{
			isRunning = false;
		}
	}
}

void SceneMenu::update()
{

}

/// <summary>
/// Effectue l'affichage de la scène
/// </summary>
void SceneMenu::draw()
{
	mainWin->clear();
	mainWin->draw(ecranTitre);
	texteScore.dessiner(mainWin);
	texteCompte.dessiner(mainWin);
	texteLogin.dessiner(mainWin);
	mainWin->display();
	
}
