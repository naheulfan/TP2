#include "Scores.h"
#include <fstream>
#include <vector>
#include <iostream>
#include <sstream>


using namespace platformer;
Scores::Scores()
{
}

Scene::scenes Scores::run()
{
	while (isRunning)
	{
		getInputs();
		update();
		draw();
	}

	return transitionVersScene;
}
bool Scores::init(RenderWindow * const window)
{
	for (int i = 0; i < 10; i++)
	{
		topTenScores[i] = -1;
	}
	font.loadFromFile("Ressources\\Fonts\\Peric.ttf");
	for (int i = 0; i < 10; i++)
	{
		scores[i].init(240, 24, sf::Vector2f(500, (i * 48) + 10),font);

		std::ifstream fichier("scores.txt");
		std::vector<std::string> lignes;
		if (fichier)
		{
			std::string line;
			int compteurLine = 0;
				while (getline(fichier, line))
				{
					++compteurLine;
					lignes.push_back(line);
					std::stringstream input_stringstream(line); //https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c
					std::string word;
					std::vector<std::string> textScores;
					std::vector<int> playerScores;
					textScores.reserve(10);
					while (getline(input_stringstream,word, ' '))
					{
						if (word != "")
						{
							playerScores.push_back(std::stoi(word));
						}
					}
					for (int k = 0; k < playerScores.size(); k++)
					{
						int temp = -1;
						for (int j = 0; j < 10; j++)
						{
							if (playerScores.at(k) > topTenScores[j])
							{
								if (temp == -1)
								{
									temp = topTenScores[j];
									topTenScores[j] = playerScores.at(k);
								}
								if (j <= 8)
								{
									std::swap(temp, topTenScores[j + 1]);
								}
								else
								{
									topTenScores[j + 1] = temp;
								}
								textScores.push_back(modele.GetNomCompte().at(k) + " :" + std::to_string(playerScores.at(k)));
							}
							
						}
					}
				}
			}
		
		fichier.close();
		
	}
	textbox1.init(480, 24, sf::Vector2f(0, 600), font);
	textbox2.init(480, 24, sf::Vector2f(0, 650), font);
	textboxErreur1.init(480, 24, sf::Vector2f(0, 1200), font);
	textboxErreur2.init(480, 24, sf::Vector2f(600, 1200), font);
	this->mainWin = window;
	return true;
}
void Scores::draw()
{
	for (int i = 0; i < 10; i++)
	{
		scores[i].dessiner(mainWin);
	}
	textbox1.dessiner(mainWin);
	textbox2.dessiner(mainWin);
	mainWin->display();
}
void Scores::update()
{

}
void Scores::getInputs()
{
	while (mainWin->pollEvent(event))
	{
		if (event.type == Event::Closed)
		{
			isRunning = false;
			transitionVersScene = Scene::scenes::SORTIE;
		}


		else if (event.type == Event::MouseButtonPressed)
		{
			//Si on touche à la textbox avec la souris

			if (textbox1.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActif = &textbox1; //Ce textbox devient actif
				textbox1.selectionner();  //on l'affiche comme étant sélectionné
										  //textboxErreurNickname.insererTexte(""); //on efface le message d'erreur (optionnel, amis ça fait clean si on fait un nouvel essai)
			}
			else if (textbox2.touche(Mouse::getPosition(*mainWin)))
			{
				textboxActif = &textbox2; //Ce textbox devient actif
				textbox2.selectionner();  //on l'affiche comme étant sélectionné
			}
			else
			{
				//Sinon aucun textbox actif
				//Ce else devrait être dans toutes vos fenêtres où il n'y a pas de textbox.
				textboxActif = nullptr;
			}


		}
		if (event.type == Event::KeyPressed && textboxActif != nullptr)
		{
			//VALIDER LES INFOS DANS TOUS LES TEXTBOX D'UNE SCÈNE
			if (event.key.code == Keyboard::Return)
			{
				enterActif = true; //Pour s'assurer que enter n'est pas saisie comme caractère

				if (textboxActif == &textbox1)
				{
					if (Controleur::GetInstance()->CompteExiste(textboxActif->getTexte()))
					{
						int noCompteActif = modele.NoCompte(textboxActif->getTexte());

					}
					else
					{
						//On affiche notre erreur.
						textboxErreur1.insererTexte("Nom invalide, veuillez recommencer");
					}
				}
				else if (textboxActif == &textbox2)
				{
					
				}
			}
			else if (event.key.code == Keyboard::BackSpace)
			{
				textboxActif->retirerChar();
				backspaceActif = true;  //Pour s'assurer que backspace n'est pas saisie comme caractère
			}
			else if (event.key.code == Keyboard::Escape)
			{
				isRunning = false;
				transitionVersScene = Controleur::GetInstance()->RequeteChangerScene(Scene::scenes::CREER_COMPTE, event);
			}
		}
		if (!backspaceActif && !enterActif && textboxActif != nullptr && (event.type == Event::TextEntered))
		{
			if (event.text.unicode < 128)
			{
				textboxActif->ajouterChar((char)event.text.unicode);
			}
		}
	}
	enterActif = false;
	backspaceActif = false;
}
