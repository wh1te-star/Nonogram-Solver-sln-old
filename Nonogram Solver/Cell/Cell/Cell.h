#ifndef CELL_H
#define CELL_H


#include "Cell/CellColor/CellColor.h"

class Cell {
private:
    CellColor color;

public:
    explicit Cell();
    explicit Cell(CellColor color);

    CellColor getColor() const;

    bool operator==(const Cell& other) const;
    bool operator!=(const Cell& other) const;

	bool canColor(CellColor newColor) const;
};

#endif
