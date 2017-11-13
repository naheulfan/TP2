#include "stdafx.h"
#include "CppUnitTest.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include "../Platformer/Modele.h"
#include "../Platformer/Controleur.h"
//Il faut que ce dernier lien soit aussi dans 
//[right-click sur projet]\éditeur de liens\propriétés\entrées\dépendances additionnelles
//sinon il y aura une erreur de linkage

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace platformer;

namespace ProjetSFMLTest
{		
	TEST_CLASS(modele)
	{
	public:
		
		TEST_METHOD(ModeleEffacerCompte)
		{
			Modele modele;

			modele.AjoutCompte("compteTest", "Test-123", "Langevin", "Bruno", "test@gmail.com");

			modele.EffacerCompte(modele.NoCompte("compteTest"));

			Assert::IsFalse(Controleur::GetInstance()->CompteExiste("compteTest"));
			std::ofstream fichier("comptes.txt");
			fichier << "";
		}

		TEST_METHOD(ModeleNoCompte)
		{
			Modele modele;
			std::vector<std::string> comptes;

			modele.AjoutCompte("compteTest", "Test-123", "Langevin", "Bruno", "test@gmail.com");
			comptes = modele.GetNomCompte();

			Assert::IsTrue(modele.NoCompte("compteTest") == comptes.size());

			std::ofstream fichier("comptes.txt");
			fichier << "";
		}

		TEST_METHOD(ModeleDonneeCompte)
		{
			Modele modele;
			std::string* compte = new std::string[5];

			compte[0] = "compteTest";
			compte[1] = "Test-123";
			compte[2] = "Langevin";
			compte[3] = "Bruno";
			compte[4] = "test@gmail.com";
			modele.AjoutCompte(compte[0], compte[1], compte[2], compte[3], compte[4]);

			Assert::IsTrue(compte[0] == modele.DonneeCompte("compteTest")[0]);
			Assert::IsTrue(compte[1] == modele.DonneeCompte("compteTest")[1]);
			Assert::IsTrue(compte[2] == modele.DonneeCompte("compteTest")[2]);
			Assert::IsTrue(compte[3] == modele.DonneeCompte("compteTest")[3]);
			Assert::IsTrue(compte[4] == modele.DonneeCompte("compteTest")[4]);

			std::ofstream fichier("comptes.txt");
			fichier << "";
		}

		TEST_METHOD(ModeleAjoutCompte)
		{
			Modele modele;

			modele.AjoutCompte("compteTest", "Test-123", "Langevin", "Bruno", "test@gmail.com");

			Assert::IsTrue(Controleur::GetInstance()->CompteExiste("compteTest"));

		}

		TEST_METHOD(ModeleGetNomCompte)
		{
			Modele modele;
			std::vector<std::string> comptes;

			modele.AjoutCompte("compteTest", "Test-123", "Langevin", "Bruno", "test@gmail.com");
			comptes = modele.GetNomCompte();

			Assert::IsTrue("compteTest" == comptes.back());

			std::ofstream fichier("comptes.txt");
			fichier << "";
		}

		TEST_METHOD(ModeleModifierCompte)
		{
			Modele modele;
			std::string* compte = new std::string[5];

			compte[0] = "compteTest";
			compte[1] = "Test-123";
			compte[2] = "Langevin";
			compte[3] = "Bruno";
			compte[4] = "test@gmail.com";
			modele.AjoutCompte(compte[0], compte[1], compte[2], compte[3], compte[4]);

			modele.ModifierCompte(compte[0], compte[1], "Test", "Dummy", "ok@ggmail.com");

			Assert::IsTrue(compte[0] == modele.DonneeCompte("compteTest")[0]);
			Assert::IsTrue(compte[1] == modele.DonneeCompte("compteTest")[1]);
			Assert::IsFalse(compte[2] == modele.DonneeCompte("compteTest")[2]);
			Assert::IsFalse(compte[3] == modele.DonneeCompte("compteTest")[3]);
			Assert::IsFalse(compte[4] == modele.DonneeCompte("compteTest")[4]);

			std::ofstream fichier("comptes.txt");
			fichier << "";
		}
	};

	TEST_CLASS(controleur)
	{
	public:

		TEST_METHOD(ControleurVerificationCompteTrue)
		{
			Modele modele;

			modele.AjoutCompte("compteTest", "Test-123", "Langevin", "Bruno", "test@gmail.com");

			Assert::IsTrue(Controleur::GetInstance()->VerificationCompte("compteTest", "Test-123"));

			std::ofstream fichier("comptes.txt");
			fichier << "";
		}

		TEST_METHOD(ControleurVerificationCompteFalse)
		{
			Modele modele;

			modele.AjoutCompte("compteTest", "Test-123", "Langevin", "Bruno", "test@gmail.com");

			Assert::IsFalse(Controleur::GetInstance()->VerificationCompte("compteTest", "123456"));

			std::ofstream fichier("comptes.txt");
			fichier << "";
		}



		TEST_METHOD(ControleurValidationCompteTrue1)
		{

			Assert::IsTrue(Controleur::GetInstance()->ValidationCompte("compteTest", "Test-123", "Langevin", "Bruno", "test@gmail.com"));

		}

		TEST_METHOD(ControleurValidationCompteFalse1)
		{
			//Nom trop court
			Assert::IsFalse(Controleur::GetInstance()->ValidationCompte("a", "Test-123", "Langevin", "Bruno", "test@gmail.com"));
		}
		TEST_METHOD(ControleurValidationCompteFalse2)
		{
			//Nom trop long
			Assert::IsFalse(Controleur::GetInstance()->ValidationCompte("abcdefghijklmnopqurtuvwxyz", "Test-123", "Langevin", "Bruno", "test@gmail.com"));
		}
		
		TEST_METHOD(ControleurValidationCompteFalse3)
		{
			Modele modele;

			modele.AjoutCompte("compteTest", "Test-123", "Langevin", "Bruno", "test@gmail.com");
			//Compte déjà existant
			Assert::IsFalse(Controleur::GetInstance()->ValidationCompte("compteTest", "Test-123", "Langevin", "Bruno", "test@gmail.com"));

			std::ofstream fichier("comptes.txt");
			fichier << "";
		}



		TEST_METHOD(ControleurValidationInfoCompte)
		{
			Assert::IsTrue(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "Langevin", "Bruno", "test@gmail.com"));
		}

		TEST_METHOD(ControleurValidationInfoCompteMotDePasse1)
		{
			Assert::IsTrue(Controleur::GetInstance()->ValidationInfoCompte("Te#st.123", "Langevin", "Bruno", "test@gmail.com"));
		}
		TEST_METHOD(ControleurValidationInfoCompteMotDePasse2)
		{
			Assert::IsTrue(Controleur::GetInstance()->ValidationInfoCompte("Te#st@12_3", "Langevin", "Bruno", "test@gmail.com"));
		}
		TEST_METHOD(ControleurValidationInfoCompteMotDePasseFalse1)
		{
			//Manque un majuscule
			Assert::IsFalse(Controleur::GetInstance()->ValidationInfoCompte("te#st.123", "Langevin", "Bruno", "test@gmail.com"));
		}
		TEST_METHOD(ControleurValidationInfoCompteMotDePasseFalse2)
		{
			//Tous les caractères sont des alphanumériques
			Assert::IsFalse(Controleur::GetInstance()->ValidationInfoCompte("Tesasdt", "Langevin", "Bruno", "test@gmail.com"));
		}

		TEST_METHOD(ControleurValidationInfoCompteNom1)
		{
			Assert::IsTrue(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "Langevin-Pleau", "Bruno", "test@gmail.com"));
		}
		TEST_METHOD(ControleurValidationInfoCompteNom2)
		{
			Assert::IsTrue(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "L.Pleau", "Bruno", "test@gmail.com"));
		}
		TEST_METHOD(ControleurValidationInfoCompteNom3)
		{
			Assert::IsTrue(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "L.Pleau-LP", "Bruno", "test@gmail.com"));
		}
		TEST_METHOD(ControleurValidationInfoCompteNomFalse1)
		{
			//Caractère spécial
			Assert::IsFalse(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "La#ngevin", "Bruno", "test@gmail.com"));
		}
		TEST_METHOD(ControleurValidationInfoCompteNomFalse2)
		{
			//Nom trop court
			Assert::IsFalse(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "L", "Bruno", "test@gmail.com"));
		}
		TEST_METHOD(ControleurValidationInfoCompteNomFalse3)
		{
			//Nom trop long
			Assert::IsFalse(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "abcdefghijklmnopqurtuvwxyz", "Bruno", "test@gmail.com"));
		}

		TEST_METHOD(ControleurValidationInfoComptePrenom1)
		{
			Assert::IsTrue(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "Langevin", "A.Bruno", "test@gmail.com"));
		}
		TEST_METHOD(ControleurValidationInfoComptePrenom2)
		{
			Assert::IsTrue(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "Langevin", "A.Bruno-Lan", "test@gmail.com"));
		}
		TEST_METHOD(ControleurValidationInfoComptePrenom3)
		{
			Assert::IsTrue(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "Langevin", "Anto-Bruno", "test@gmail.com"));
		}
		TEST_METHOD(ControleurValidationInfoComptePrenomFalse1)
		{
			//Caractère spécial
			Assert::IsFalse(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "Langevin", "Bru#no", "test@gmail.com"));
		}
		TEST_METHOD(ControleurValidationInfoComptePrenomFalse2)
		{
			//Prenom trop court
			Assert::IsFalse(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "Langevin", "B", "test@gmail.com"));
		}
		TEST_METHOD(ControleurValidationInfoComptePrenomFalse3)
		{
			//Prenom trop long
			Assert::IsFalse(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "Langevin", "abcdefghijklmnopqurtuvwxyz", "test@gmail.com"));
		}

		TEST_METHOD(ControleurValidationInfoCompteCourriel1)
		{
			Assert::IsTrue(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "Langevin", "Anto-Bruno", "te-st@gmail.ca"));
		}
		TEST_METHOD(ControleurValidationInfoCompteCourriel2)
		{
			Assert::IsTrue(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "Langevin", "Anto-Bruno", "te_st@hotmail.com"));
		}
		TEST_METHOD(ControleurValidationInfoCompteCourrielFalse1)
		{
			//"@" après le "."
			Assert::IsFalse(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "Langevin", "Anto-Bruno", "te-st.gmail@ca"));
		}
		TEST_METHOD(ControleurValidationInfoCompteCourrielFalse2)
		{
			//Pas de "@"
			Assert::IsFalse(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "Langevin", "Anto-Bruno", "te_sthotmail.com"));
		}
		TEST_METHOD(ControleurValidationInfoCompteCourrielFalse3)
		{
			//Pas de "."
			Assert::IsFalse(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "Langevin", "Anto-Bruno", "te-st@gmailca"));
		}
		TEST_METHOD(ControleurValidationInfoCompteCourrielFalse4)
		{
			//Domaine trop court
			Assert::IsFalse(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "Langevin", "Anto-Bruno", "te_st@hotmailcom."));
		}
		TEST_METHOD(ControleurValidationInfoCompteCourrielFalse5)
		{
			//Domaine trop long
			Assert::IsFalse(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "Langevin", "Anto-Bruno", "te_st@gmail.hotmailcom"));
		}
		TEST_METHOD(ControleurValidationInfoCompteCourrielFalse6)
		{
			//Rien en avant du "@"
			Assert::IsFalse(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "Langevin", "Anto-Bruno", "@gmail.com"));
		}
		TEST_METHOD(ControleurValidationInfoCompteCourrielFalse7)
		{
			//Rien entre le "@" et le "."
			Assert::IsFalse(Controleur::GetInstance()->ValidationInfoCompte("Test-123", "Langevin", "Anto-Bruno", "asdf@.com"));
		}



		TEST_METHOD(ControleurValidationInfoRequeteEffacerCompte1)
		{
			Modele modele;

			modele.AjoutCompte("compteTest", "Test-123", "Langevin", "Bruno", "test@gmail.com");
			
			Assert::IsTrue(Controleur::GetInstance()->RequeteEffacerCompte("compteTest", "Test-123"));
			Assert::IsFalse(Controleur::GetInstance()->CompteExiste("compteTest"));
			std::ofstream fichier("comptes.txt");
			fichier << "";
		}
		TEST_METHOD(ControleurValidationInfoRequeteEffacerCompteFalse1)
		{
			Modele modele;

			modele.AjoutCompte("compteTest", "Test-123", "Langevin", "Bruno", "test@gmail.com");
			//Mauvais mot de passe
			Assert::IsFalse(Controleur::GetInstance()->RequeteEffacerCompte("compteTest", "Te-123"));
			Assert::IsTrue(Controleur::GetInstance()->CompteExiste("compteTest"));

			std::ofstream fichier("comptes.txt");
			fichier << "";
		}

		TEST_METHOD(ControleurCompteExiste1)
		{
			Modele modele;

			modele.AjoutCompte("compteTest", "Test-123", "Langevin", "Bruno", "test@gmail.com");

			Assert::IsTrue(Controleur::GetInstance()->CompteExiste("compteTest"));

			std::ofstream fichier("comptes.txt");
			fichier << "";
		}
		TEST_METHOD(ControleurCompteExisteFalse1)
		{
			Assert::IsFalse(Controleur::GetInstance()->CompteExiste("compteTest"));
		}


		TEST_METHOD(ControleurRequeteModificationCompte1)
		{

			Modele modele;
			std::string* compte = new std::string[5];
			std::string* compteNew = new std::string[5];

			compte[0] = "compteTest";
			compte[1] = "Test-123";
			compte[2] = "Langevin";
			compte[3] = "Bruno";
			compte[4] = "test@gmail.com";
			modele.AjoutCompte(compte[0], compte[1], compte[2], compte[3], compte[4]);

			Assert::IsTrue(Controleur::GetInstance()->RequeteModificationCompte(compte[0], compte[1], "Test", "Dummy", "ok@ggmail.com"));
			compteNew = modele.DonneeCompte("compteTest");
			Assert::IsTrue(compte[0] == compteNew[0]);
			Assert::IsTrue(compte[1] == compteNew[1]);
			Assert::IsFalse(compte[2] == compteNew[2]);
			Assert::IsFalse(compte[3] == compteNew[3]);
			Assert::IsFalse(compte[4] == compteNew[4]);

			std::ofstream fichier("comptes.txt");
			fichier << "";
		}
		TEST_METHOD(ControleurRequeteModificationCompte2)
		{
			Modele modele;
			std::string* compte = new std::string[5];

			compte[0] = "compteTest";
			compte[1] = "Test-123";
			compte[2] = "Langevin";
			compte[3] = "Bruno";
			compte[4] = "test@gmail.com";
			modele.AjoutCompte(compte[0], compte[1], compte[2], compte[3], compte[4]);

			Assert::IsTrue(Controleur::GetInstance()->RequeteModificationCompte(compte[0], compte[1], compte[2], compte[3], compte[4]));
			Assert::IsTrue(compte[0] == modele.DonneeCompte("compteTest")[0]);
			Assert::IsTrue(compte[1] == modele.DonneeCompte("compteTest")[1]);
			Assert::IsTrue(compte[2] == modele.DonneeCompte("compteTest")[2]);
			Assert::IsTrue(compte[3] == modele.DonneeCompte("compteTest")[3]);
			Assert::IsTrue(compte[4] == modele.DonneeCompte("compteTest")[4]);

			std::ofstream fichier("comptes.txt");
			fichier << "";
		}
		TEST_METHOD(ControleurRequeteModificationCompteFalse1)
		{
			Modele modele;
			std::string* compte = new std::string[5];

			compte[0] = "compteTest";
			compte[1] = "Test-123";
			compte[2] = "Langevin";
			compte[3] = "Bruno";
			compte[4] = "test@gmail.com";
			modele.AjoutCompte(compte[0], compte[1], compte[2], compte[3], compte[4]);

			//Mot de passe non valide
			Assert::IsFalse(Controleur::GetInstance()->RequeteModificationCompte(compte[0], "est123", compte[2], compte[3], compte[4]));
			Assert::IsTrue(compte[0] == modele.DonneeCompte("compteTest")[0]);
			Assert::IsTrue(compte[1] == modele.DonneeCompte("compteTest")[1]);
			Assert::IsTrue(compte[2] == modele.DonneeCompte("compteTest")[2]);
			Assert::IsTrue(compte[3] == modele.DonneeCompte("compteTest")[3]);
			Assert::IsTrue(compte[4] == modele.DonneeCompte("compteTest")[4]);

			std::ofstream fichier("comptes.txt");
			fichier << "";
		}
	};
}