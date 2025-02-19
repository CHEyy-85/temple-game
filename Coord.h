#ifndef COORD_H
#define COORD_H

class Coord
{
    public:
        Coord();
        Coord(int row, int col);
        bool operator==(const Coord& other) const;
        int getRow() const;
        int getCol() const;
        void setRow(int row);
        void setCol(int col);

    private:
        int m_row;
        int m_col;
};

#endif