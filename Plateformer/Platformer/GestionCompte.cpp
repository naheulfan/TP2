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

bool GestionCompte::init(RenderWindow * const window)
{
	//if (!ecranTitreT.loadFromFile("Ressources\\Sprites\\Title.png"))
	//{
	//	return false;
	//}

	if (!font.loadFromFile("Ressources\\Fonts\\Peric.ttf"))
	{
		return false;
	}

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

	//ecranTitre.setTexture(ecranTitreT);

	this->mainWin = window;
	isRunning = true;

	return true;
}

void GestionCompte::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}

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

void GestionCompte::draw()
{
	mainWin->clear();
	titre.dessiner(mainWin);
	texteCreer.dessiner(mainWin);
	texteModifier.dessiner(mainWin);
	texteEffacer.dessiner(mainWin);
	texteMenu.dessiner(mainWin);
	mainWin->display();

}