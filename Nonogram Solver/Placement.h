#ifndef PLACEMENT_H
#define PLACEMENT_H


#include <vector>
#include "Cell.h"
#include "CellLocation.h"
#include "Coordinate.h"

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
