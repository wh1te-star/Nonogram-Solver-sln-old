#include "Cell/Cell/Cell.h"
#include "Cell/CellLocation/CellLocation.h"
#include "Index/Coordinate/Coordinate.h"

CellLocation::CellLocation(Coordinate coordinate, Cell cell) :
    coordinate(coordinate), cell(cell) {}

bool CellLocation::operator==(const CellLocation& other) const {
	return coordinate == other.coordinate && cell == other.cell;
}

bool CellLocation::operator!=(const CellLocation& other) const {
    return !(*this == other);
}

Coordinate CellLocation::getCoordinate() const {
    return coordinate;
}

Cell CellLocation::getCell() const {
    return cell;
}
