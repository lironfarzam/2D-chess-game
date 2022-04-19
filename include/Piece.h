#pragma once

#include <iostream>
#include <Windows.h>
#include <string>
#include "Location.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

class Piece
{
public:
	Piece(Location,string);
	~Piece();
	Location getLocation() const;
	
	void setLocation(Location);
	string getColor()const;
	virtual int directionForLocation(Location);


	virtual bool legalMoveForDirection(Location) = 0;

protected:
	string m_color = "";
	Location m_location = { 0,0 };

private:
	

};
