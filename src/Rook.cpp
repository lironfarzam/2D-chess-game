#pragma once

#include "Rook.h"

Rook::Rook(Location loc, string color):Piece(loc,color)
{
}

Rook::~Rook()
{
}

bool Rook::legalMoveForDirection(Location des)
{
	return(m_location.m_row == des.m_row ||
			m_location.m_col == des.m_col);
}


