#ifndef ROWPLACEMENT_H
#define ROWPLACEMENT_H


#include "Index/Coordinate/Coordinate.h"
#include "Placement/Placement/Placement.h"

class RowPlacement : public Placement {
public:
    explicit RowPlacement(std::vector<Cell> placement);

	const std::vector<CellLocation> getCellLocationList(const Coordinate& coordinate) const override;
};


#endif
