#pragma once

#include "Bishop.h"

Bishop::Bishop(Location loc, string color) :Piece(loc, color)
{
}

Bishop::~Bishop()
{
}

bool Bishop::legalMoveForDirection(Location des)
{

	for (int i = 1; i < 8; i++)
	{
		if (abs(m_location.m_row - des.m_row) == i && abs(m_location.m_col - des.m_col) == i)
		{
			return true;
		}
	}
	return false;
}


