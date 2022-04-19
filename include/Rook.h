#pragma once

#include "Piece.h"

class Rook : virtual public Piece
{
public:
	Rook(Location, string);
	~Rook();

	virtual bool legalMoveForDirection(Location) override;

private:
	

};
