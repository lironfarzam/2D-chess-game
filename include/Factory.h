#pragma once

#include "Const.h"
#include "Piece.h"
#include "King.h"
#include "Rook.h"
#include "Bishop.h"
#include "Queen.h"



// a singleton factory to create game objects

class Factory {
public:
	~Factory();
	static Factory& instance();

	std::unique_ptr<Piece> createPiece(char, int,int);

private:
	Factory();
	Factory(const Factory&) = default;
	Factory& operator=(const Factory&) = default;

};