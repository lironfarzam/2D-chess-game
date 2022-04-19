#pragma once

#include <iostream>
#include <Windows.h>
#include <string>
#include <vector>
#include "Location.h"
#include "Piece.h"
#include "Factory.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;


class Board
{
public:
	Board(string);
	~Board();
	void switchTurn();
	string getTurn();

	int statusCheckForCode(string,bool);
	
	bool isLegalStepForThePiece(const Location, const Location);
	bool isLegalStepForTheRange(const Location, const Location);
	bool movementWillCauseCheckmate(const Location, const Location);
	bool movementWasLegalandCauseCheck(const Location, const Location);
	void movePiece(const Location, const Location);


private:


	string m_turn = "WHITE";
	unique_ptr<Piece> m_board[BOARD_SIZE][BOARD_SIZE] = {0};
	Location m_whiteKing;
	Location m_blackKing;

	void updataKings(const Location,const Location);

		
	


};
