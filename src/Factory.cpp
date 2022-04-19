#pragma once

#include "Factory.h"


#include <iostream>

/*
*  A SINGLETON factory to create game objects
*/

Factory::~Factory()
{
}

Factory& Factory::instance()
{
    static Factory inst;
    return inst;
}


Factory::Factory()
{
}

std::unique_ptr<Piece> Factory::createPiece(char type, int row , int col)
{
    switch (type)
    {
        case (WHITE_KING):
            return std::make_unique<King>(Location{ row,col }, "WHITE");

        case (BLACK_KING):
            return std::make_unique<King>(Location{ row,col }, "BLACK");
        
        case (WHITE_QUEEN):
            return std::make_unique<Queen>(Location{ row,col }, "WHITE");

        case (BLACK_QUEEN):
            return std::make_unique<Queen>(Location{ row,col }, "BLACK");

        case (WHITE_ROOK):
            return std::make_unique<Rook>(Location{ row,col} , "WHITE");
        
        case (BLACK_ROOK):
            return std::make_unique<Rook>(Location{ row,col} , "BLACK");

        case (WHITE_BISHOP):
            return std::make_unique<Bishop>(Location{ row,col }, "WHITE");

        case (BLACK_BISHOP):
            return std::make_unique<Bishop>(Location{ row,col }, "BLACK");

    }
    return nullptr;
}

