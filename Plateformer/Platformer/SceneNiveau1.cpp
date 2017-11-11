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
		if (!joueur.GetIsFrozen())
		{
			getInputs();
		}
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
	gemsTexture.loadFromFile("Ressources\\Sprites\\Gem.png");
	GemSprite.setTexture(gemsTexture);
	isRunning = true;
	gameStarted = false;
	initialFloor = true;
	score = 0;
	font.loadFromFile("Ressources\\Fonts\\Peric.ttf");
	scoreText.setFont(font);
	scoreText.setPosition(10, 10);
	scoreText.setString("Score: ");
	return true;

}

void SceneNiveau1::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		//x sur la fenêtre
		if (event.type == Event::Closed)
		{
			//Attention, ici simplement fermer la fenêtre ne mettrait pas nécessairement 
			//fin à l'application
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

	//Méthode binaire: appuyer à gauche et à droite sumultanément va donner 3, et le personnage ne se dépalcera alors pas.
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
			if (!joueur.GetIsFrozen())
			{
				joueur.SetJump(true);
			}
		}
		joueur.Jump();
		gameStarted = true;
	}
	if (gameStarted)
	{
		if (!joueur.GetJump())
		{
			bool uneCollision = false;
			for (int i = 0; i < 3; i++)
			{
				//Chexk avec tous les blocs
				if (joueur.CollisionPlateforme(section[0].GetPositions()[i], section[0].GetSizes()[i], TAILLE_TUILES_Y) || joueur.CollisionPlateforme(section[1].GetPositions()[i], section[1].GetSizes()[i], TAILLE_TUILES_Y))
				{
					uneCollision = true;
				}
				if (!uneCollision)
				{
					joueur.SetIsFalling(true);
				}

				//for (int i = 0; i < NOMBRE_TUILES_X; ++i)
				//{
				//	joueur.Gravity(Vector2f(i, mainWin->getSize().y - TAILLE_TUILES_Y * 2), TAILLE_TUILES_X, TAILLE_TUILES_Y);
				//}
			}
			if (joueur.getPosition().y < mainWin->getSize().y - 2 * TAILLE_TUILES_Y)
			{
				joueur.Gravity();
			}
			else if (!initialFloor)
			{
				joueur.Gravity();
			}
			else(joueur.SetIsFalling(false));
		}
		if (section[0].GetPositions()[0].y >= mainWin->getSize().y)
		{
			int sectionNumber = std::rand() % 3 + 1;
			section[0] = *SectionGenerator::GenerateSection(sectionNumber);
			if (initialFloor)
			{
				initialFloor = false;
			}
			int ennemiNumber = std::rand() % 3;
			int ennemiPlateform = std::rand() % 3;
			listeEnnemis.push_back(FabriqueEnnemi::GenerateEnnemi(ennemiNumber, section[0].GetPositions()[ennemiPlateform], section[0].GetSizes()[ennemiPlateform]));
			if (ennemiNumber == 0)
			{
				gems.push_back(Gems(sf::Vector2f(section[0].GetPositions()[ennemiPlateform].x + section[0].GetSizes()[ennemiPlateform] / 2, section[0].GetPositions()[ennemiPlateform].y - TAILLE_TUILES_Y)));
			}
		}
		else if ((section[0].GetPositions()[0].y >= mainWin->getSize().y / 2) && (section[1].GetPositions()[0].y >= mainWin->getSize().y / 2))
		{
			int sectionNumber = std::rand() % 3 + 1;
			section[1] = *SectionGenerator::GenerateSection(sectionNumber);
			int ennemiNumber = std::rand() % 3;
			int ennemiPlateform = std::rand() % 3;
			listeEnnemis.push_back(FabriqueEnnemi::GenerateEnnemi(ennemiNumber, section[1].GetPositions()[ennemiPlateform], section[1].GetSizes()[ennemiPlateform]));
			if (ennemiNumber == 0)
			{
				gems.push_back(Gems(sf::Vector2f(section[1].GetPositions()[ennemiPlateform].x + section[1].GetSizes()[ennemiPlateform] / 2, section[1].GetPositions()[ennemiPlateform].y - TAILLE_TUILES_Y)));
			}
		}
		section[0].Update();
		section[1].Update();
		for (int i = 0; i < listeEnnemis.size(); i++)
		{
			listeEnnemis.at(i)->Update();
			if (listeEnnemis.at(0)->Getposition().y >= mainWin->getSize().y)
			{
				listeEnnemis.erase(listeEnnemis.begin());//en théorie le premier élément de la liste c'est le plus bas
			}
			if (joueur.CollisionEnnemis(listeEnnemis.at(i)->Getposition(), listeEnnemis.at(i)->GetWidth(), listeEnnemis.at(i)->GetHeight()))
			{
				if (listeEnnemis.at(i)->GetEnnemiType() == 0)
				{
					joueur.Freeze();
				}
				else if (listeEnnemis.at(i)->GetEnnemiType() == 1)
				{
					joueur.Confuse();
					listeEnnemis.at(i)->Attack();
				}
				else if (listeEnnemis.at(i)->GetEnnemiType() == 2)
				{
					joueur.SlimeSlow();
				}
			}
		}
		for (int i = 0; i < gems.size(); i++)
		{
			gems.at(i).Update();
			if (joueur.CollisionEnnemis(gems.at(i).GetPosition(), GemSprite.getTextureRect().width, GemSprite.getTextureRect().height))
			{
				gems.erase(gems.begin() + i);
				score += 5;
			}
		}
		if (scoreClock.getElapsedTime() >= sf::seconds(3))
		{
			score++;
			scoreClock.restart();
		}
		scoreText.setString("score: " + std::to_string(score));
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
			if (grilleDeTuiles[x][y] != nullptr && initialFloor)
			{
				mainWin->draw(*grilleDeTuiles[x][y]);
			}
		}
	section[0].Draw(*mainWin);
	section[1].Draw(*mainWin);
	for (int i = 0; i < listeEnnemis.size(); i++)
	{
		listeEnnemis[i]->Draw(*mainWin);
	}
	for (int i = 0; i < gems.size(); i++)
	{
		gems.at(i).Draw(GemSprite, *mainWin);
	}
	mainWin->draw(joueur);
	mainWin->draw(scoreText);
	mainWin->display();
}

