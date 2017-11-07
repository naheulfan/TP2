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
	if (!ecranTitreT.loadFromFile("Ressources\\Sprites\\Title.png"))
	{
		return false;
	}

	if (!font.loadFromFile("Ressources\\Fonts\\Peric.ttf"))
	{
		return false;
	}

	titre.setString("Gestion compte");
	titre.setFont(font);
	titre.setCharacterSize(50);
	titre.setFillColor(Color::White);

	texteModifier.setString("\"E\" pour effacer un compte");
	texteModifier.setFont(font);
	texteModifier.setCharacterSize(20);
	texteModifier.setFillColor(Color::White);

	texteEffacer.setString("\"M\" pour modifier un compte");
	texteEffacer.setFont(font);
	texteEffacer.setCharacterSize(20);
	texteEffacer.setFillColor(Color::White);

	texteCreer.setString("\"C\" pour creer un compte");
	texteCreer.setFont(font);
	texteCreer.setCharacterSize(20);
	texteCreer.setFillColor(Color::White);


	ecranTitre.setTexture(ecranTitreT);

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
	titre.setPosition(mainWin->getSize().x / 2 - 175, 80);
	texteCreer.setPosition(mainWin->getSize().x / 2 - 120, mainWin->getSize().y - 100);
	texteEffacer.setPosition(mainWin->getSize().x / 2 - 120, mainWin->getSize().y - 130);
	texteModifier.setPosition(mainWin->getSize().x / 2 - 120, mainWin->getSize().y - 160);
}

void GestionCompte::draw()
{
	mainWin->clear();
	mainWin->draw(titre);
	mainWin->draw(texteEffacer);
	mainWin->draw(texteCreer);
	mainWin->draw(texteModifier);
	mainWin->display();

}