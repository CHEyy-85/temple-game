#include "Coord.h"

Coord::Coord(): m_row(0), m_col(0){}

Coord::Coord(int row, int col): m_row(row), m_col(col){}

bool Coord::operator==(const Coord& other) const
{
    return m_row == other.m_row && m_col == other.m_col;
}

int Coord::getRow() const
{
    return m_row;
}

int Coord::getCol() const
{
    return m_col;
}

void Coord::setRow(int row)
{
    m_row = row;
}

void Coord::setCol(int col)
{
    m_col = col;
}