#include "..\include\King.h"

King::King(Location loc, string color) :Piece(loc, color)
{
}

King::~King()
{
}

bool King::legalMoveForDirection(Location des)
{
	return( abs(m_location.m_row - des.m_row) <= 1 && 
		    abs(m_location.m_col - des.m_col) <= 1 );
}


