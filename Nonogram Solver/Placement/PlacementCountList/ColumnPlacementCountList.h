#ifndef COLUMNPLACEMENTCOUNTLIST_H
#define COLUMNPLACEMENTCOUNTLIST_H


#include "Placement/PlacementCountList/PlacementCountList.h"
#include "Index/CellIndex/ColumnIndex.h"

class ColumnPlacementCountList : public PlacementCountList {
public:
    explicit ColumnPlacementCountList(std::vector<PlacementCount> placementCountList);

public:
    PlacementCount operator[](ColumnIndex index) const;
};


#endif
