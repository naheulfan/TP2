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

bool SceneMenu::init(RenderWindow * const window)
{
	if (!ecranTitreT.loadFromFile("Ressources\\Sprites\\Title.png"))
	{
		return false;
	}

	if (!font.loadFromFile("Ressources\\Fonts\\Peric.ttf"))
	{
		return false;
	}

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

void SceneMenu::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}

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

void SceneMenu::draw()
{
	mainWin->clear();
	mainWin->draw(ecranTitre);
	texteScore.dessiner(mainWin);
	texteCompte.dessiner(mainWin);
	texteLogin.dessiner(mainWin);
	mainWin->display();
	
}
