#pragma once

#include "Piece.h"

class Bishop : virtual public Piece
{
public:
	Bishop(Location, string);
	~Bishop();

	virtual bool legalMoveForDirection(Location) override;

private:


};
