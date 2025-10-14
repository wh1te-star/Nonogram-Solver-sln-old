#include "Placement/Placement/Placement.h"
#include "Cell/Cell/Cell.h"
#include "Index/Coordinate/Coordinate.h"

Placement::Placement(std::vector<Cell> placement) :
    placement(placement) {}

const std::vector<Cell>& Placement::getPlacement() const {
    return placement;
}

bool Placement::operator==(const Placement& other) const {
	return placement == other.placement;
}

bool Placement::operator!=(const Placement& other) const {
    return !(*this == other);
}
