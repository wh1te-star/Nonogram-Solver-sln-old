#include "Placement/PlacementCountList/PlacementCountList.h"
#include <algorithm>
#include "Placement/PlacementCount/PlacementCount.h"


PlacementCountList::PlacementCountList(std::vector<PlacementCount> placementCountList) :
	placementCountList(placementCountList) {}

const std::vector<PlacementCount>& PlacementCountList::getPlacementCountList() const {
	return placementCountList;
}

bool PlacementCountList::operator==(const PlacementCountList& other) const {
    return placementCountList == other.placementCountList;
}

bool PlacementCountList::operator!=(const PlacementCountList& other) const {
    return !(*this == other);
}
