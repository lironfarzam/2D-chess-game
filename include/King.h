#pragma once

#include "Piece.h"

class King : virtual public Piece
{
public:
	King(Location, string);
	~King();

	virtual bool legalMoveForDirection(Location) override;
	
private:


};
