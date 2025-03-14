#include "chess.h"

#include <stdlib.h>
#include <time.h>

#include <sstream>
#include <iostream>
#include <fstream>
using namespace std;

Square::Square()
{
	piece = EMPTY;
	color = NONE;
}

void Square::setSpace(Square* space)
{
	color = space->getColor();
	piece = space->getPiece();
}

void Square::setEmpty()
{
	color = NONE;
	piece = EMPTY;
}

Piece Square::getPiece()
{
	return piece;
}

Color Square::getColor()
{
	return color;
}

void Square::setPieceAndColor(Piece p, Color c)
{
	piece = p;
	color = c;

}

void Board::superOrdi(){
	int caca=0;
	int random=0;
	srand(time(NULL));
	int i=0;

	random = rand()%64;
	
	
	
	while (square[int(((random+i)/8))%8]
				 [(random+i)%8].getColor()!=BLACK){i++;}
				 
	//cout << "####" << endl ;
	int x1 = int(((random+i)/8))%8;
	int y1 = (random+i)%8;
	
	i = 0;
	
	bool stop = false;
	
	while (!stop){ 
		
		//cout <<"IS BLACK ? :"<< (square[x1][y1].getColor()==BLACK) << endl;
		if (makeMove(x1, y1, int(((random+i)/8))%8, (random+i)%8)){stop = true;}
		i++;
	}

	//cout << "FIN ORDI" << endl;
	

}


void Board::printBoard() {
	using namespace std;
	cout << "   y: 0 1 2 3 4 5 6 7 " << endl << "x:" << endl;
	
	for (int i = 0; i < 8; i++)
	{
		cout << " " << i << "   ";
		for (int j = 0; j < 8; j++)
		{
			Piece p = square[i][j].getPiece();
			Color c = square[i][j].getColor();

			
			switch (p)
			{
			case QUEEN: (c == WHITE) ? cout << " R" : cout << " r";
				break;
			case BISHOP:(c == WHITE) ? cout << " F" : cout << " f";
				break;
			case KNIGHT:(c == WHITE) ? cout << " C" : cout << " c";
				break;
			case ROOK: (c == WHITE) ? cout << " T" : cout << " t";
				break;
			case EMPTY: cout << "  ";
				break;
			default: cout << "XX";
				break;
			}

		}
		cout << endl;
	}
	
	

}

void Board::lectSave(){
	
	ifstream MyFile("projet_echec/saves/save.txt");
	
	char p='n';
	int i=0;
	string myText;
		
	while (getline (MyFile, myText)) {
		
		
		p = myText[0];
		
		//cout << "p : " << p << endl;
		
		//Piece pion = EMPTY;
		//Color color = NONE;
	
		switch (int(p))
			{				
			case int('R') : square[int(i/8)][i%8].setPieceAndColor(QUEEN,WHITE) ; break ;
			case int('F') : square[int(i/8)][i%8].setPieceAndColor(BISHOP,WHITE) ; break ;
			case int('C') : square[int(i/8)][i%8].setPieceAndColor(KNIGHT,WHITE) ; break ;
			case int('T') : square[int(i/8)][i%8].setPieceAndColor(ROOK,WHITE) ; break ;
			
			case int('r') : square[int(i/8)][i%8].setPieceAndColor(QUEEN,BLACK) ; break ;
			case int('f') : square[int(i/8)][i%8].setPieceAndColor(BISHOP,BLACK) ; break ;
			case int('c') : square[int(i/8)][i%8].setPieceAndColor(KNIGHT,BLACK) ; break ;
			case int('t') : square[int(i/8)][i%8].setPieceAndColor(ROOK,BLACK) ; break ;
			
			case int('0') : turn = WHITE; break;
			case int('1') : turn = BLACK; break;
			case int('2') : turn = ORDI; break;
			}
		
		i++;
	}
	
	
	MyFile.close();
	//cin >> p;
	for (int i = 0; i < 8; i++){
	for (int j = 0; j < 8; j++){
			square[i][j].setX(i);
			square[i][j].setY(j);
		}
    }
    
    //printBoard();
}

void Board::save(){
	
	///////////////////////////////////////// Tentative de sauvegarder plusieurs parties
	/*ofstream idFile("projet_echec//saves//idSave.txt");

	cout << idFile.is_open() <<  endl;
	idFile << "truc";
	//int id = 0;
	//string temp = "";
	//string myText;
	
	//stringstream stoi;
	
	
	
	//stoi >> id;
	
	
	
	idFile.close();*/
	
	
	
	//Je sais pas pourquoi, le fichier ne peut être ouvert UNIQUEMENT si il n'existe pas. Or, l'idée de la sauvegarde c'est de créer un fichier.
	//Donc un bon moyen serait de à chaque fois créer un nouveau fichier avec un nom différents, mais impossible de garder en mémoire les noms déjà utilisés 
	//puisque je ne peux pas faire de fichier de sauvegarde. J'ai le cas du serpent qui se mord la queue.
	
	ofstream MyFile("projet_echec/saves/save.txt");
	
	//MyFile.open;
	
	//cout << MyFile.is_open() <<  endl;
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			Piece p = square[i][j].getPiece();
			Color c = square[i][j].getColor();

			
			switch (p)
			{
			case QUEEN: (c == WHITE) ? MyFile << "R" : MyFile << "r";
				break;
			case BISHOP:(c == WHITE) ? MyFile << "F" : MyFile << "f";
				break;
			case KNIGHT:(c == WHITE) ? MyFile << "C" : MyFile << "c";
				break;
			case ROOK: (c == WHITE) ? MyFile << "T" : MyFile << "t";
				break;
			case EMPTY: MyFile << "N";
				break;
			default: MyFile << "X";
				break;
			}
			MyFile << endl;
		}
		
	}
	MyFile << turn;
	MyFile.close();
	

}



bool Board::doMove() {
	
	string move;
	int x1, x2, y1, y2;
	bool stop = false;
	
	Piece destPiece;
	Color srcColor;
	
	
	if (turn == ORDI) {superOrdi();}
			
	else {
		while (!stop)
		{
			
			if (turn == WHITE) {cout << "Au tour des Blancs : " << endl ;} 
			if (turn == BLACK) {cout << "Au tour des Noirs : " << endl;}
			
			cout << "Entrez votre coup : " << endl;
			cin >> move;
			
			if (move == "save"){save(); cout<<"Jeu sauvegarde !" << endl; return false;}
			//if (move == "del"){delFile(); cout<<"delete !" << endl; return false;}		
			x1 = move[0] - 48;
			y1 = move[1] - 48;
			x2 = move[2] - 48;
			y2 = move[3] - 48;
			
			
			destPiece = (getSquare(x2, y2)->getPiece());
			//cout << "destPiece : " << destPiece << endl;
			
			srcColor = (getSquare(x1, y1)->getColor());
			//cout << "srcColor : " << srcColor << endl;
			
			//cout <<"turn : "<< getSquare(x1, y1)->getColor() <<" ; " << turn  << " ; " << WHITE << " ; " << BLACK << " ; "  << NONE << endl;
			if (getSquare(x1, y1)->getColor() == turn)
			{
	
	
				if (!makeMove(x1, y1, x2, y2))
				{cout << "Coup invalide, Essayez encore." << endl;}
				else
					{stop = true;}
			}
			else
				{cout << "Ce n'est pas votre pièce. Essayez encore." << endl;}
		
		}
	}
	
	bool whiteWin = true;
	bool blackWin = true;
	
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			{
				//Piece p = square[i][j].getPiece();
				Color c = square[i][j].getColor();
				
				if (c == WHITE){blackWin = false;}
				if (c == BLACK){whiteWin = false;}
			}
	}
	//cout << "BLANCS : " << whiteWin << endl << "NOIRS : " << blackWin << endl;
	
	if (blackWin){
		if (ordinateur){cout << "L'ordinateur a gagné !" << endl;} 
		else {cout << "Les Noirs ont gagne !"<<endl;}
		return false;
		}
	if (whiteWin){cout << "Les Blancs ont gagne !" << endl;return false;}
		
	//cout << "check" << endl;
	//cin >> x1;

	
	if (turn == WHITE){
		
		if (ordinateur){turn = ORDI;}
		else{turn = BLACK;}
	}
	else{turn = WHITE;}
	
	

	return true;
}

void Board::setBoard()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
			square[j][i].setPieceAndColor(EMPTY, NONE);

	}
	
	square[0][0].setPieceAndColor(ROOK, WHITE);
	square[1][0].setPieceAndColor(KNIGHT, WHITE);
	square[2][0].setPieceAndColor(BISHOP, WHITE);
	square[3][0].setPieceAndColor(QUEEN, WHITE);
	//square[4][0].setPieceAndColor(KING, WHITE);
	square[5][0].setPieceAndColor(BISHOP, WHITE);
	square[6][0].setPieceAndColor(KNIGHT, WHITE);
	square[7][0].setPieceAndColor(ROOK, WHITE);

	square[0][7].setPieceAndColor(ROOK, BLACK);
	square[1][7].setPieceAndColor(KNIGHT, BLACK);
	square[2][7].setPieceAndColor(BISHOP, BLACK);
	square[3][7].setPieceAndColor(QUEEN, BLACK);
	//square[4][7].setPieceAndColor(KING, BLACK);
	square[5][7].setPieceAndColor(BISHOP, BLACK);
	square[6][7].setPieceAndColor(KNIGHT, BLACK);
	square[7][7].setPieceAndColor(ROOK, BLACK);


	
	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			square[i][j].setX(i);
			square[i][j].setY(j);
		}
    }

}

bool Board::playGame()
{
	system("cls");
	
	printBoard();
	return doMove();

}

/*bool Board::moveKing(Square* thisKing, Square* thatSpace) {
	using namespace std;
	//off board inputs should be handled elsewhere (before this)
	//squares with same color should be handled elsewhere (before this)
	
	if ((abs(thatSpace->getX() - thisKing->getX()) == 1) || (abs(thatSpace->getY() - thisKing->getY()) == 1)) 
		{
			thatSpace->setSpace(thisKing);
			thisKing->setEmpty();
			return true;
		}
	return false;
}*/

bool Board::moveQueen(Square* thisQueen, Square* thatSpace) { //there might be problems with numbers of brackets
													   //off board inputs should be handled elsewhere (before this)
													   //squares with same color should be handled elsewhere (before this)

	int queenX = thisQueen->getX();
	int queenY = thisQueen->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();

	int yIncrement;
	int xIncrement;

	bool invalid = false;
	if (queenX != thatX || queenY != thatY)
	{

		if (queenX == thatX)
		{
			yIncrement = (thatY - queenY) / (abs(thatY - queenY));
			for (int i = queenY + yIncrement; i != thatY; i += yIncrement)
			{

				if (square[thatX][i].getColor() != NONE)
					return false;

			}
		}
		else
			if (queenY == thatY)
			{

				xIncrement = (thatX - queenX) / (abs(thatX - queenX));
				for (int i = queenX + xIncrement; i != thatX; i += xIncrement)
				{
					if (square[i][thatY].getColor() != NONE)
						return false;
				}
			}
			else
				if (abs(queenX - thatX) == abs(queenY - thatY))
				{
					xIncrement = (thatX - queenX) / (abs(thatX - queenX));
					yIncrement = (thatY - queenY) / (abs(thatY - queenY));

					for (int i = 1; i < abs(queenX - thatX); i++)
					{
						std::cout << "Comment est-ce possible ?";
						if (square[queenX + xIncrement*i][queenY + yIncrement*i].getColor() != NONE)
							return false;

					}
				}
				else
					return false;
	}



	if (invalid == false)
	{
		thatSpace->setSpace(thisQueen);
		thisQueen->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}

bool Board::moveBishop(Square* thisBishop, Square* thatSpace) { //there might be problems with number of brackets
	int bishopX = thisBishop->getX();
	int bishopY = thisBishop->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	Square *s;
	if (abs(bishopX - thatX) == abs(bishopY - thatY))
	{
		int xIncrement = (thatX - bishopX) / (abs(thatX - bishopX));
		int yIncrement = (thatY - bishopY) / (abs(thatY - bishopY));

		for (int i = 1; i < abs(bishopX - thatX); i++)
		{
			std::cout << "Comment est-ce possible ?";
			if (square[bishopX + xIncrement*i][bishopY + yIncrement*i].getColor() != NONE)
				return false;

		}
	}
	else
		return false;

	if (invalid == false)
	{
		thatSpace->setSpace(thisBishop);
		thisBishop->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}
bool Board::moveKnight(Square* thisKnight, Square* thatSpace)
{
	//off board inputs should be handled elsewhere (before this)
	//squares with same color should be handled elsewhere (before this)
	int knightX = thisKnight->getX();
	int knightY = thisKnight->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();

	if ((abs(knightX - thatX) == 2 && abs(knightY - thatY) == 1) || (abs(knightX - thatX) == 1 && abs(knightY - thatY) == 2))
	{
		thatSpace->setSpace(thisKnight);
		thisKnight->setEmpty();
		return true;
	}
	else
	{
		return false;
	}
}

bool Board::moveRook(Square* thisRook, Square* thatSpace)
{
	//off board inputs should be handled elsewhere (before this)
	//squares with same color should be handled elsewhere (before this)
	int rookX = thisRook->getX();
	int rookY = thisRook->getY();
	int thatX = thatSpace->getX();
	int thatY = thatSpace->getY();
	bool invalid = false;
	if (rookX != thatX || rookY != thatY)
	{

		if (rookX == thatX)
		{
			int yIncrement = (thatY - rookY) / (abs(thatY - rookY));
			for (int i = rookY + yIncrement; i != thatY; i += yIncrement)
			{

				if (square[thatX][i].getColor() != NONE)
					return false;

			}
		}
		else
			if (rookY == thatY)
			{

				int xIncrement = (thatX - rookX) / (abs(thatX - rookX));
				for (int i = rookX + xIncrement; i != thatX; i += xIncrement)
				{
					if (square[i][thatY].getColor() != NONE)
						return false;
				}
			}
			else
				return false;
	}
	if (!invalid)
	{
		thatSpace->setSpace(thisRook);
		thisRook->setEmpty();
		return true;
	}
	else
	{//Return some erorr or something. Probably return false;
		std::cout << "Ce n'est pas un coup valide pour une tour'";
		return false;
	}
}


bool Board::makeMove(int x1, int y1, int x2, int y2) {
	//Checking for turns will be done previous to this
	using namespace std;
	if (x1 < 0 || x1>7 || y1 < 0 || y1>7 || x2 < 0 || x2>7 || y2 < 0 || y2>7)
	{
		cout << "x1 : " << x1 << endl << "y1 : " << y1 << endl << "x2 : " << x2 << endl << "y2 : " << y2 << endl;
		cout << (square[x1][y1].getColor()!=BLACK) << endl;
		//cin >> x1;
		
		std::cout << "Coup invalide : Fuite, une de vos entrees est hors limites !" << std::endl;
		return false;
	}
	Square* src = getSquare(x1, y1);
	Square* dest = getSquare(x2, y2);

	if (src->getColor() == dest->getColor())
	{
		std::cout << "Coup invalide : Cannibalisme, vous ne pouvez pas vous manger vous meme !" << std::endl;
		return false;
	}
	
	switch (src->getPiece())
	{
	/*case KING: return moveKing(src, dest);
		break;*/
	case QUEEN: return moveQueen(src, dest);
		break;
	case BISHOP: return moveBishop(src, dest);
		break;
	case KNIGHT: return moveKnight(src, dest);
		break;
	case ROOK: return moveRook(src, dest);
		break;
	case EMPTY: std::cout << "Coup invalide : Schizophrenie, vous n'avez pas de pièce ici !" << std::endl 
		<< "x1 : " << x1 << endl << "y1 : " << y1 << endl << "x2 : " << x2 << endl << "y2 : " << y2 << endl << endl;
		cout << (square[x1][y1].getColor()!=BLACK) << endl;
		//cin >> x1;  
		return false;
	
		break;
	default: std::cerr << "Something went wrong in the switch statement in makeMove()" << std::endl;
		break;
	}
	return false;
}
