#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include "chess.h"



using namespace std;

/*void menu(){
	//public ordinateur;
	
	//public ordinateur;
	Board b;
	
	bool newgame = true;
	
	int s=-1;
	
	while(s!=0){
		
		cout << "___MENU ECHEC___" << endl;
		cout << "1 - Jouer contre un joueur local" << endl;
		cout << "2 - Jouer contre un ordinateur" << endl;
		cout << "3 - Continuer une partie sauvegardee" << endl;
		cout << "Entrez votre choix : " << endl;
		
		cin >> s;
		
		
		switch(s){
			case 1 : ordinateur = false; b.setBoard(); while(b.playGame());break;
			case 2 : ordinateur = true; b.setBoard(); while(b.playGame());break;
			case 3 : b.lectSave(); break;
		}
		
		
		
		
		/*while (b.playGame());
		{
			cout << "Do you want to play again? (y for yes, anything else for no) ";
			cin >> s;
			if (s != "y")
				{newgame = false;}
		}*
	}

}*/

void how2play(){
	cout << "Pour jouer, choisissez d'abord votre piece; Et notez ses coordonnees x et y ." << endl;
	cout << "Ensuite, choisissez sa destination; Et notez les coordonnees x et y de la destination ." << endl;
	cout << "Pour entrer votre coup, il vous suffit de d'ecrire les 4 coordonnees concatenees ." << endl;
	cout << "Par exemple, pour jouer votre reine qui est a la case (3,1) a la case (5,3); " << endl;
	cout << "Vous ecrirez : 3153" << endl;
}


int main()
{
	
	
	cout << "   _____ _    _ ______  _____ _____ "<< endl
		  <<"  / ____| |  | |  ____|/ ____/ ____| "<< endl
		  <<" | |    | |__| | |__  | (___| (___  "<< endl
		  <<" | |    |  __  |  __|  \\___  \\___ \\ "<< endl
		  <<" | |____| |  | | |____ ____) |___) | "<< endl
		  <<"  \\_____|_|  |_|______|_____/_____/ \n" << endl;
	cout << "Jeu par Sacha Gramatikoff et Serenic Mohanraju."<<endl;
	cout << "A n'improte quel moment de la partie, tapez " << '"'  <<"save"<< '"'<< " pour sauvegarder." << endl;
	
	Board b;
	b.ordinateur = true;
	
	bool newgame = true;
	
	int s=-1;
	
	while(s!=0){
		
		cout << endl << "___MENU ECHEC___" << endl;
		cout << "1 - Jouer contre un joueur local" << endl;
		cout << "2 - Jouer contre un ordinateur" << endl;
		cout << "3 - Continuer une partie sauvegardee" << endl;
		cout << "4 - Comment jouer ?" << endl;
		cout << "0 - Quitter le jeu" << endl;
		cout << "Entrez votre choix : " << endl;
		
		cin >> s;
		
		
		switch(s){
			case 1 : b.ordinateur = false; b.setBoard(); while(b.playGame());break;
			case 2 : b.ordinateur = true; b.setBoard(); while(b.playGame());break;
			case 3 : b.lectSave(); while(b.playGame()); break;
			case 4 : how2play(); break;
		}
		
		
		
		
		/*while (b.playGame());
		{
			cout << "Do you want to play again? (y for yes, anything else for no) ";
			cin >> s;
			if (s != "y")
				{newgame = false;}
		}*/
	}

	return 0;
}




