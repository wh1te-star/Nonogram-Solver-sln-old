#ifndef CELLLOCATION_H
#define CELLLOCATION_H


#include "Index/Coordinate/Coordinate.h"
#include "Cell/Cell/Cell.h"

class CellLocation {
private:
	Coordinate coordinate;
	Cell cell;

public:
    explicit CellLocation(Coordinate coordinate, Cell cell);

public:
    const Coordinate& getCoordinate() const;
    const Cell& getCell() const;

public:
    bool operator==(const CellLocation& other) const;
    bool operator!=(const CellLocation& other) const;
};

#endif
