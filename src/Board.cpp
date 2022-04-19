#pragma once

#include "Board.h"


Board::Board(string str)
/* C-tor: get the setup of the board. 
*  by using the factiory add all the pieces
*/
{
	int row = 0;
	int col = 0;
	for (char c : str) 
	{
		if (c == BLACK_KING)//black king
			m_blackKing = { row,col };
		if (c == WHITE_KING)//white king
			m_whiteKing= { row,col };

		std::unique_ptr<Piece>temp = Factory::instance().createPiece(c, row,col);
		m_board[row][col] = std::move(temp);
		col++;
		if (col >= BOARD_SIZE)
		{
			col = 0;
			row++;
		}
	}
}

Board::~Board()
/* D-tor release all the pointers
*/
{
	for (int i = 0; i < BOARD_SIZE; i++) 
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (m_board[i][j] != nullptr)
				m_board[i][j].release();
		}
	}
}

void Board::switchTurn()
{
	m_turn = m_turn == "WHITE" ? "BLACK" : "WHITE";
}

string Board::getTurn()
{
	return m_turn;
}

int Board::statusCheckForCode(string res, bool checkChessstatus)
{
	int sourceRow = (res[0] - 'a');
	int sourceCol = (res[1] - '1');
	int targetRow = (res[2] - 'a');
	int targetCol = (res[3] - '1');


	//11 - there is not piece at the source
	if (m_board[sourceRow][sourceCol] == NULL)
		return 11;

	//12 - the piece in the source is piece of your opponent
	if (checkChessstatus && m_board[sourceRow][sourceCol]->getColor() != m_turn)
		return 12;
	
	//13 - there one of your pieces at the destination
	if (checkChessstatus && m_board[targetRow][targetCol] != NULL &&
		m_board[targetRow][targetCol]->getColor() == m_turn)
		return 13;
	
	//21 - illegal movement of that piece
	if (!isLegalStepForThePiece({ sourceRow , sourceCol } , { targetRow , targetCol }) ||
		!isLegalStepForTheRange({ sourceRow , sourceCol }, { targetRow , targetCol }))
		return 21;

	//30 - Just check if the next situation will cause chess
	if (!checkChessstatus)
		return 30;

	//31 - this movement will cause you checkmate
	if (movementWillCauseCheckmate({ sourceRow , sourceCol }, { targetRow , targetCol }))
		return 31;

	//legal movements :
	
	//41 - the last movement was legal and cause check)
	if (movementWasLegalandCauseCheck({ sourceRow , sourceCol }, { targetRow , targetCol }))
		return 41;
	
	//42 - the last movement was legal, next turn)
	return 42;


}

bool Board::isLegalStepForThePiece(const Location src, const Location des)
{
	return m_board[src.m_row][src.m_col]->legalMoveForDirection(des);
}

bool Board::isLegalStepForTheRange(Location src, Location des)
/*In chess it is forbidden to skip the tools.
  Therefore we get from each tool the direction it needs to go
  to reach the destination (according to the arrangement of the keys)
  and according to the direction we check if the route to the
  destination is free.

  7 8 9
  4 * 6
  1 2 3

  (In the future to add a rider that moves differently you could use
  codes like 86 to symbolize up and right)
*/
{
	int row = src.m_row;
	int col = src.m_col;


	switch (m_board[src.m_row][src.m_col]->directionForLocation(des))
	{
	case(8):
		row--;
		while (row > 0 && row > des.m_row)
		{
			if (m_board[row][col] != nullptr)
				return false;
			row--;
		}
		return true;
		break;
	case(2):
		row++;
		while (row < BOARD_SIZE && row < des.m_row)
		{
			if (m_board[row][col] != nullptr)
				return false;
			row++;
		}
		return true;
		break;
	case(4):
		col--;
		while (col > 0 && col > des.m_col)
		{
			if (m_board[row][col] != nullptr)
				return false;
			col--;
		}
		return true;
		break;
	case(6):
		col++;
		while (col < BOARD_SIZE && col < des.m_col)
		{
			if (m_board[row][col] != nullptr)
				return false;
			col++;
		}
		return true;
		break;

	case(7):
		col--; row--;
		while (col > 0 && row > 0 && col > des.m_col)
		{
			if (m_board[row][col] != nullptr)
				return false;
			col--; row--;
		}
		return true;
		break;

	case(9):
		col++; row--;
		while (col < BOARD_SIZE && row > 0 && col < des.m_col)
		{
			if (m_board[row][col] != nullptr)
				return false;
			col++; row--;
		}
		return true;
		break;

	case(1):
		col--; row++;
		while (col > 0 && row < BOARD_SIZE && col > des.m_col)
		{
			if (m_board[row][col] != nullptr)
				return false;
			col--; row++;
		}
		return true;
		break;

	case(3):
		col++; row++;
		while (col < BOARD_SIZE && row < BOARD_SIZE && col < des.m_col)
		{
			if (m_board[row][col] != nullptr)
				return false;
			col++; row++;
		}
		return true;
		break;

	default:
		return false;
		break;
	}

}

bool Board::movementWillCauseCheckmate(const Location src, const Location des)
/*To check future status we move the tool and check all possible options
  of the opponent in the next by mini recursion ...
  If we have reached the state of chess (code 30), we will 
  return to the previous state and announce that the move is illegal
*/
{
	auto temp = std::move(m_board[des.m_row][des.m_col]);
	movePiece(src, des);
	updataKings(src, des);

	Location myKing = m_turn == "WHITE" ? m_whiteKing : m_blackKing;

	
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (m_board[i][j] != nullptr && m_board[i][j]->getColor() != m_turn)
			{
				string nextMove;
				nextMove = (i + 'a');
				nextMove += (j + '1');
				nextMove += (myKing.m_row + 'a');
				nextMove += (myKing.m_col + '1');
				
				int val = statusCheckForCode(nextMove, false);
				if (val >= 30)
				{
					movePiece(des, src);
					m_board[des.m_row][des.m_col] = std::move(temp);

					updataKings(des, src);

					return true;
				}	
			}
		}
	}
	temp.release();
	return false;

}

bool Board::movementWasLegalandCauseCheck(const Location src, const Location des)
/* Since chess can happen from any tool in the game and not just
   the one that moves this time there is no choice these check all
   the tools that are in the motherboard they are able to reach the
   opponent king in legal.
*/
{
	Location enamyKing = m_turn != "WHITE" ? m_whiteKing : m_blackKing;
	
	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (m_board[i][j] != nullptr && m_board[i][j]->getColor() == m_turn)
			{
				string nextMove;
				nextMove = (i + 'a');
				nextMove += (j + '1');
				nextMove += (enamyKing.m_row + 'a');
				nextMove += (enamyKing.m_col + '1');

				if (statusCheckForCode(nextMove, false) >= 30)
				{
					return true;
				}
			}
		}
	}
	return false;
}

void Board::movePiece(const Location src, const Location des)
{
	m_board[src.m_row][src.m_col]->setLocation(des);
	m_board[des.m_row][des.m_col] = std::move(m_board[src.m_row][src.m_col]);
}

void Board::updataKings(const Location src, const Location des)
{
	if (m_whiteKing == src)
		m_whiteKing = des;
	if (m_blackKing == src)
		m_blackKing = des;
}

