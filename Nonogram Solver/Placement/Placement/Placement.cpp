#include "Placement/Placement/Placement.h"
#include "Cell/Cell/Cell.h"
#include "Index/Coordinate/Coordinate.h"

Placement::Placement(Coordinate coordinate, std::vector<Cell> placement) :
    coordinate(coordinate), placement(placement) {}

bool Placement::operator==(const Placement& other) const {
	return coordinate == other.coordinate && placement == other.placement;
}

bool Placement::operator!=(const Placement& other) const {
    return !(*this == other);
}
