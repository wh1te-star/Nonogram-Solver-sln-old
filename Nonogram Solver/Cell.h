#ifndef CELL_H
#define CELL_H


#include "CellColor.cpp"

class Cell {
private:
    CellColor color;

public:
    explicit Cell();
    explicit Cell(CellColor color);

    CellColor get() const;

    bool operator==(const Cell& other) const;
    bool operator!=(const Cell& other) const;

	bool canColor(CellColor newColor) const;
};

#endif
