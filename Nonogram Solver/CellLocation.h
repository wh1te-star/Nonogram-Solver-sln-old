#ifndef CELLLOCATION_H
#define CELLLOCATION_H


#include "Coordinate.h"
#include "Cell.h"

class CellLocation {
private:
	Coordinate coordinate;
	Cell cell;

public:
    explicit CellLocation(Coordinate coordinate, Cell cell);

    bool operator==(const CellLocation& other) const;
    bool operator!=(const CellLocation& other) const;

    Coordinate getCoordinate() const;
    Cell getCell() const;
};

#endif
