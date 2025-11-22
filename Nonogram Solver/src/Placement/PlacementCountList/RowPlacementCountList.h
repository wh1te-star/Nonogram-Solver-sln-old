#ifndef ROWPLACEMENTCOUNTLIST_H
#define ROWPLACEMENTCOUNTLIST_H


#include "Placement/PlacementCountList/PlacementCountList.h"
#include "Placement/PlacementCount/PlacementCount.h"
#include "Index/CellIndex/RowIndex.h"

class RowPlacementCountList : public PlacementCountList {
public:
    explicit RowPlacementCountList(std::vector<PlacementCount> placementCountList);

public:
    const PlacementCount& operator[](RowIndex index) const; 
    PlacementCount& operator[](RowIndex index); 
};


#endif
