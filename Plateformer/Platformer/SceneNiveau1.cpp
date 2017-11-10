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
	section[0] = *SectionGenerator::GenerateSection(1);
	DragonTexture.loadFromFile("Ressources\\Sprites\\Dragon.png");
	dragon = Dragon(section[0].GetPositions()[0], DragonTexture, section[0].GetSizes()[0]);
	ChevalierTexture.loadFromFile("Ressources\\Sprites\\Paladin.png");
	SlimeTexture.loadFromFile("Ressources\\Sprites\\Slime.png");
	slime = Slime(section[0].GetPositions()[2], SlimeTexture, section[0].GetSizes()[2]);
	chevalier = Chevalier(section[0].GetPositions()[1], ChevalierTexture, section[0].GetSizes()[1]);
	gemsTexture.loadFromFile("Ressources\\Sprites\\Gem.png");
	GemSprite.setTexture(gemsTexture);
	gems[0] = Gems(sf::Vector2f(section[0].GetPositions()[0].x + section[0].GetSizes()[0] / 2, section[0].GetPositions()[0].y - 20));
	isRunning = true;
	gameStarted = false;
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
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || joueur.GetJump() || joueur.GetIsFalling())
	{
		interfaceCommande |= 4;
		if (!joueur.GetJump() && !joueur.GetIsFalling())
		{
			joueur.SetJump(true);
		}
		joueur.Jump();
		gameStarted = true;
	}
	if (gameStarted)
	{
		if (!joueur.GetJump() && joueur.GetIsFalling())
		{
			for (int i = 0; i < 3; i++)
			{
				//Chexk avec tous les blocs
				joueur.Collision(section[0].GetPositions()[i], section[0].GetSizes()[i], TAILLE_TUILES_Y);
				joueur.Collision(section[1].GetPositions()[i], section[1].GetSizes()[i], TAILLE_TUILES_Y);
				//for (int i = 0; i < NOMBRE_TUILES_X; ++i)
				//{
				//	joueur.Gravity(Vector2f(i, mainWin->getSize().y - TAILLE_TUILES_Y * 2), TAILLE_TUILES_X, TAILLE_TUILES_Y);
				//}
			}
			joueur.Gravity();
		}
		if (section[0].GetPositions()[0].y >= mainWin->getSize().y)
		{
			section[0] = *SectionGenerator::GenerateSection(2);
		}
		else if (section[0].GetPositions()[0].y >= mainWin->getSize().y / 2)
		{
			section[1] = *SectionGenerator::GenerateSection(3);
		}

		section[0].Update();
		section[1].Update();
		dragon.Update();
		chevalier.Update();
		slime.Update();
		gems[0].Update();
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
	section[0].Draw(*mainWin);
	section[1].Draw(*mainWin);
	dragon.Draw(*mainWin);
	chevalier.Draw(*mainWin);
	slime.Draw(*mainWin);
	gems[0].Draw(GemSprite, *mainWin);
	mainWin->draw(joueur);
	mainWin->display();
}

