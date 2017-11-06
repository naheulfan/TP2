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

	texteLogin.setString("Espace pour continuer");
	texteLogin.setFont(font);
	texteLogin.setCharacterSize(20);
	texteLogin.setFillColor(Color::White);

	texteScore.setString("Tab pour les scores");
	texteScore.setFont(font);
	texteScore.setCharacterSize(20);
	texteScore.setFillColor(Color::White);

	texteCompte.setString("'c' pour la gestion de compte");
	texteCompte.setFont(font);
	texteCompte.setCharacterSize(20);
	texteCompte.setFillColor(Color::White);
	

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
	texteScore.setPosition(mainWin->getSize().x / 2 - 95, mainWin->getSize().y - 100);
	texteCompte.setPosition(mainWin->getSize().x / 2 - 145, mainWin->getSize().y - 130);
	texteLogin.setPosition(mainWin->getSize().x / 2 - 110, mainWin->getSize().y - 160);
}

void SceneMenu::draw()
{
	mainWin->clear();
	mainWin->draw(ecranTitre);
	mainWin->draw(texteScore);
	mainWin->draw(texteCompte);
	mainWin->draw(texteLogin);
	mainWin->display();
	
}
