#pragma once

#include "Queen.h"

Queen::Queen(Location loc, string color) :Piece(loc, color), Bishop(loc, color), Rook(loc, color)
{
}

Queen::~Queen()
{
}

bool Queen::legalMoveForDirection(Location des)
{
	return Bishop::legalMoveForDirection(des) || Rook::legalMoveForDirection(des);
}


