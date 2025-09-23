#include "placement.h"
#include "Cell.h"

Placement::Placement(std::vector<Cell> placement) :
	placement(placement) {}

bool Placement::operator==(const Placement& other) const {
	return placement == other.placement;
}

bool Placement::operator!=(const Placement& other) const {
    return !(*this == other);
}

