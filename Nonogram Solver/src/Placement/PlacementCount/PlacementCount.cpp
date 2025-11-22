#include "Placement/PlacementCount/PlacementCount.h"

PlacementCount::PlacementCount(int count) : count(count) {}

PlacementCount PlacementCount::operator+(const PlacementCount& other) const {
    return PlacementCount(count + other.count);
}

PlacementCount PlacementCount::operator-(const PlacementCount& other) const {
    return PlacementCount(count - other.count);
}

PlacementCount& PlacementCount::operator+=(const PlacementCount& other) {
    count += other.count;
    return *this;
}

PlacementCount& PlacementCount::operator-=(const PlacementCount& other) {
    count -= other.count;
    return *this;
}

bool PlacementCount::operator<(const PlacementCount& other) const {
	return count < other.count;
}

bool PlacementCount::operator>(const PlacementCount& other) const {
	return count > other.count;
}

bool PlacementCount::operator<=(const PlacementCount& other) const {
	return count <= other.count;
}

bool PlacementCount::operator>=(const PlacementCount& other) const {
	return count >= other.count;
}

bool PlacementCount::operator==(const PlacementCount& other) const {
    return count == other.count;
}

bool PlacementCount::operator!=(const PlacementCount& other) const {
	return !(*this == other);
}

int PlacementCount::getCount() const {
    return count;
}

void PlacementCount::setCount(PlacementCount placementCount) {
    count = placementCount.count;
}
