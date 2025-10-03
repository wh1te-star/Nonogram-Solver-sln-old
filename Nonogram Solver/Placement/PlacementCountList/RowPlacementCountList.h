#ifndef ROWPLACEMENTCOUNTLIST_H
#define ROWPLACEMENTCOUNTLIST_H


#include "Placement/PlacementCountList/PlacementCountList.h"
#include "Placement/PlacementCount/PlacementCount.h"

class RowPlacementCountList : public PlacementCountList {
public:
    explicit RowPlacementCountList(std::vector<PlacementCount> placementCountList);
};


#endif
