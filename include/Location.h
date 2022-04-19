#pragma once

#include <iostream>
using namespace std;

struct Location {
    int m_row = 0;
    int m_col = 0;
    bool operator== (const Location& loc);
    /*
    void operator+= (const Location& loc);
    void operator*= (const Location& loc);
    bool operator!= (const Location& loc);*/


};
//Location operator* (const Location& a, const int b);
//Location operator+ (const Location& a, const Location& b);
//ostream& operator<< (ostream& os, const Location& loc);
//
