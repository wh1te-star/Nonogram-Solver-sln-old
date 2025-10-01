#include "Placement/PlacementCount/PlacementCount.h"

PlacementCount::PlacementCount(int count) : count(count) {}

int PlacementCount::getCount() const {
    return count;
}

bool PlacementCount::operator==(const PlacementCount& other) const {
    return count == other.count;
}

bool PlacementCount::operator!=(const PlacementCount& other) const {
	return !(*this == other);
}
