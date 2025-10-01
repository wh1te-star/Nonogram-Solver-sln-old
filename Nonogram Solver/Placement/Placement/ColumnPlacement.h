#ifndef COLUMNPLACEMENT_H
#define COLUMNPLACEMENT_H


#include "Placement/Placement/Placement.h"
#include "Index/Coordinate/Coordinate.h"

class ColumnPlacement : public Placement {
public:
    explicit ColumnPlacement(Coordinate coordinate, std::vector<Cell> placement);
    std::vector<CellLocation> getCellLocationList() override;
};


#endif
