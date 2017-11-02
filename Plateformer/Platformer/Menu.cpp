#include "Menu.h"

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
		transitionVersScene = Controleur::GetInstance()->requeteChangerScene(Scene::scenes::MENU, event);
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
	mainWin->display();
}
