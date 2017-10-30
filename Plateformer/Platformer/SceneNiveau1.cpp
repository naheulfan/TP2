#include "SceneNiveau1.h"

using namespace platformer;

SceneNiveau1::SceneNiveau1()
{
	for (int x=0; x < NOMBRE_TUILES_X; x++)
		for (int y = 0; y < NOMBRE_TUILES_Y; y++)
		{
			grilleDeTuiles[x][y] = nullptr;
		}
}

SceneNiveau1::~SceneNiveau1()
{
	for (int x = 0; x < NOMBRE_TUILES_X; x++)
		for (int y = 0; y < NOMBRE_TUILES_Y; y++)
		{
			if (grilleDeTuiles[x][y] != nullptr)
			{
				delete grilleDeTuiles[x][y];
			}
		}
}

Scene::scenes SceneNiveau1::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}

bool SceneNiveau1::init(RenderWindow * const window)
{
	for (int i = 0; i < TUILES_ROUGES; i++)
	{
		if (!tuilesRougesT[i].loadFromFile("Ressources\\Tiles\\BlockA" + std::to_string(i) + ".png"))
		{
			return false;
		}
	}

	for (int i = 0; i < BACKGROUNDS; i++)
	{
		if (!backgroundT[i].loadFromFile("Ressources\\Backgrounds\\Layer" + std::to_string(i) + "_1.png"))
		{
			return false;
		}
	}

	if (!joueur.init(0, window->getSize().x, "Ressources\\Sprites\\Player\\Player.png"))
	{
		return false;
	}
	
	for (int i = 0; i < BACKGROUNDS; i++)
	{
		background[i].setTexture(backgroundT[i]);
	}
	
	srand(time(NULL));

	for (int x = 0; x < NOMBRE_TUILES_X; x++)
	{
		//Choix du bloc au hasard
		grilleDeTuiles[x][NOMBRE_TUILES_Y - 1] = new Sprite(tuilesRougesT[rand() % TUILES_ROUGES]);
		grilleDeTuiles[x][NOMBRE_TUILES_Y - 1]->setPosition(x * TAILLE_TUILES_X, TAILLE_TUILES_Y * (NOMBRE_TUILES_Y - 1));
	}

	//Position arbitraire pour le joueur en x, pas arbitraire en y (sur le plancher)
	joueur.setPosition(100, window->getSize().y - TAILLE_TUILES_Y * 2);

	this->mainWin = window;
	isRunning = true;
	plateformeTexture.loadFromFile("Ressources\\Tiles\\BlockA0.png");
	plateformesBlock1[0] = Plateforme(400, Vector2f(50, 50), plateformeTexture);
	plateformesBlock1[1] = Plateforme(100, Vector2f(400, 250), plateformeTexture);
	plateformesBlock1[2] = Plateforme(230, Vector2f(400, 400), plateformeTexture);
	return true;
}

void SceneNiveau1::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		//x sur la fen�tre
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fen�tre ne mettrait pas n�cessairement 
			//fin � l'application
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}

		if (event.type == Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				isRunning = false;
				transitionVersScene = Scene::scenes::TITRE;
			}
		}
	}

	interfaceCommande = 0;

	//M�thode binaire: appuyer � gauche et � droite sumultan�ment va donner 3, et le personnage ne se d�palcera alors pas.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		interfaceCommande |= 1;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D))
	{
		interfaceCommande |= 2;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		interfaceCommande |= 4;
	}
}

void SceneNiveau1::update()
{
	if (interfaceCommande == 1)
	{
		joueur.move(-1);
	}
	else if(interfaceCommande == 2)
	{
		joueur.move(1);
	}
	if (interfaceCommande == 4 || joueur.GetJump())
	{
		joueur.SetJump(true);
		joueur.Jump();
	}
	//else if (!joueur.GetJump())
	//{
	//	joueur.Gravity();
	//}
	for (int i = 0; i < 3; i++)
	{
		plateformesBlock1[i].SetPosition(Vector2f(plateformesBlock1[i].GetPosition().x, plateformesBlock1[i].GetPosition().y + 1));
	}
}

void SceneNiveau1::draw()
{
	mainWin->clear();

	for (int i = 0; i < BACKGROUNDS; i++)
	{
		mainWin->draw(background[i]);
	}

	for (int x = 0; x < NOMBRE_TUILES_X; x++)
		for (int y = 0; y < NOMBRE_TUILES_Y; y++)
		{
			if (grilleDeTuiles[x][y] != nullptr)
			{
				mainWin->draw(*grilleDeTuiles[x][y]);
			}
		}
	
	mainWin->draw(joueur);
	for (int i = 0; i < 3; i++)
	{
		plateformesBlock1[i].Draw(*mainWin);
	}
	mainWin->display();
}

