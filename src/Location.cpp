#include "Location.h"

bool Location::operator==(const Location& loc)
{
    return m_col == loc.m_col && m_row == loc.m_row;
}
