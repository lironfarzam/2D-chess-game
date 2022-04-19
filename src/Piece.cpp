#pragma once

#include "Piece.h"


Piece::Piece(Location loc, const string color):m_color(color),m_location(loc)
{
}

Piece::~Piece()
{
}

inline Location Piece::getLocation() const
{
	return m_location;
}

void Piece::setLocation(Location loc)
{
	m_location = loc;
}

string Piece::getColor() const
{
	return m_color;
}

int Piece::directionForLocation(Location des)
{
	if (m_location.m_row > des.m_row && m_location.m_col == des.m_col)
		return 8;
	if (m_location.m_row < des.m_row && m_location.m_col == des.m_col)
		return 2;
	if (m_location.m_col > des.m_col && m_location.m_row == des.m_row)
		return 4;
	if (m_location.m_col < des.m_col && m_location.m_row == des.m_row)
		return 6;
	for (int i = 1; i < 8; i++)
	{
		if (m_location.m_row == des.m_row + i && m_location.m_col == des.m_col + i)
			return 7;
		if (m_location.m_row == des.m_row + i && m_location.m_col == des.m_col - i)
			return 9;
		if (m_location.m_row == des.m_row - i && m_location.m_col == des.m_col + i)
			return 1;
		if (m_location.m_row == des.m_row - i && m_location.m_col == des.m_col - i)
			return 3;
	}

	return 5;

}
