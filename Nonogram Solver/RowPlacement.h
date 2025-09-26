#ifndef ROWPLACEMENT_H
#define ROWPLACEMENT_H


#include "Coordinate.h"
#include "Placement.h"

class RowPlacement : public Placement {
public:
    explicit RowPlacement(Coordinate coordinate, std::vector<Cell> placement);
    std::vector<CellLocation> getCellLocationList() override;
};


#endif
