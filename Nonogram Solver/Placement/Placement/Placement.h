#ifndef PLACEMENT_H
#define PLACEMENT_H


#include <vector>
#include "Cell/Cell/Cell.h"
#include "Cell/CellLocation/CellLocation.h"
#include "Index/Coordinate/Coordinate.h"

class Placement {
private:

protected:
    Coordinate coordinate;
    std::vector<Cell> placement;

    explicit Placement(Coordinate coordinate, std::vector<Cell> placement);

public:
    virtual ~Placement() = default;
    bool operator==(const Placement& other) const;
    bool operator!=(const Placement& other) const;

    virtual std::vector<CellLocation> getCellLocationList() = 0;
};

#endif
