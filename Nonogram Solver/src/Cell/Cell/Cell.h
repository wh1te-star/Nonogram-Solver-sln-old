#ifndef CELL_H
#define CELL_H


#include "Cell/CellColor/CellColor.h"

class Cell {
private:
    CellColor color;

public:
    explicit Cell();
    explicit Cell(CellColor color);

public:
    const CellColor& getColor() const;

public:
    bool operator==(const Cell& other) const;
    bool operator!=(const Cell& other) const;

public:
	bool canColor(const CellColor& newColor) const;
};

#endif
