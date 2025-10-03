#ifndef COLUMNPLACEMENTCOUNTLIST_H
#define COLUMNPLACEMENTCOUNTLIST_H


#include "Placement/PlacementCountList/PlacementCountList.h"

class ColumnPlacementCountList : public PlacementCountList {
public:
    explicit ColumnPlacementCountList(std::vector<PlacementCount> placementCountList);
};


#endif
