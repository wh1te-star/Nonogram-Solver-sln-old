#include "Placement/PlacementCount/PlacementCount.h"

PlacementCount::PlacementCount(int count) : count(count) {}

const int& PlacementCount::getCount() const {
    return count;
}

PlacementCount PlacementCount::operator+(const PlacementCount& other) const {
    return PlacementCount(count + other.count);
}

PlacementCount PlacementCount::operator-(const PlacementCount& other) const {
    return PlacementCount(count - other.count);
}

bool PlacementCount::operator==(const PlacementCount& other) const {
    return count == other.count;
}

bool PlacementCount::operator!=(const PlacementCount& other) const {
	return !(*this == other);
}
