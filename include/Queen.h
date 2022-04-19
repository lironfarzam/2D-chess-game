#pragma once

#include "Piece.h"
#include "Bishop.h"
#include "Rook.h"

class Queen : public Bishop, public Rook
{
public:
	Queen(Location, string);
	~Queen();

	virtual bool legalMoveForDirection(Location) override;

private:


};
