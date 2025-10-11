#include "Placement/PlacementCountList/RowPlacementCountList.h"

#include "Placement/PlacementCount/PlacementCount.h"
#include "Index/CellIndex/RowIndex.h"

RowPlacementCountList::RowPlacementCountList(std::vector<PlacementCount> placementCountList) :
	PlacementCountList(placementCountList) {}

PlacementCount RowPlacementCountList::operator[](RowIndex index) const {
	return placementCountList[index.getIndex()];
}
