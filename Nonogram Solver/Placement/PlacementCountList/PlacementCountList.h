#ifndef PLACEMENTCOUNTLIST_H
#define PLACEMENTCOUNTLIST_H


#include <vector>
#include "Placement/PlacementCount/PlacementCount.h"

class PlacementCountList {
protected:
	std::vector<PlacementCount> placementCountList;

protected:
    explicit PlacementCountList(std::vector<PlacementCount> placementCountList);
public:
    virtual ~PlacementCountList() = default;

public:
    const std::vector<PlacementCount>& getPlacementCountList() const;

public:
    bool operator==(const PlacementCountList& other) const;
    bool operator!=(const PlacementCountList& other) const;
};

#endif
