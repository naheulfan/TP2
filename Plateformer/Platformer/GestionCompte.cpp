#include "GestionCompte.h"
#include "Controleur.h"

using namespace platformer;

GestionCompte::GestionCompte()
{
}

Scene::scenes GestionCompte::run()
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
bool GestionCompte::init(RenderWindow * const window)
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
	titre.initInfoTitre(Vector2f(430,80),font,false);
	titre.insererTexte("Gestion compte");

	texteCreer.initInfo(Vector2f(430, 260), font, false);
	texteCreer.insererTexte("\"C\" pour creer un compte");

	texteModifier.initInfo(Vector2f(430, 290), font, false);
	texteModifier.insererTexte("\"E\" pour effacer un compte");

	texteEffacer.initInfo(Vector2f(430, 320), font,false);
	texteEffacer.insererTexte("\"D\" pour modifier un compte");

	texteMenu.initInfo(Vector2f(430, 350), font, false);
	texteMenu.insererTexte("\"M\" pour revenir au menu principal");

	ecranTitre.setTexture(ecranTitreT);

	this->mainWin = window;
	isRunning = true;

	return true;
}

/// <summary>
/// Reçoit les évènements du joueur
/// </summary>
void GestionCompte::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}
		//Changement de scène
		transitionVersScene = Controleur::GetInstance()->RequeteChangerScene(Scene::scenes::GESTION_COMPTE, event);
		if (transitionVersScene != Scene::scenes::GESTION_COMPTE)
		{
			isRunning = false;
		}
	}
}

void GestionCompte::update()
{

}

/// <summary>
/// Effectue l'affichage de la scène
/// </summary>
void GestionCompte::draw()
{
	mainWin->clear();
	mainWin->draw(ecranTitre);
	titre.dessiner(mainWin);
	texteCreer.dessiner(mainWin);
	texteModifier.dessiner(mainWin);
	texteEffacer.dessiner(mainWin);
	texteMenu.dessiner(mainWin);
	mainWin->display();
}