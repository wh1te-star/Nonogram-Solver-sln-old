#ifndef PLACEMENT_H
#define PLACEMENT_H


#include <vector>
#include "Cell.h"
#include "Coordinate.h"

class Placement {
private:
    Coordinate coordinate;
    std::vector<Cell> placement;

protected:
    explicit Placement(Coordinate coordinate, std::vector<Cell> placement);
    virtual ~Placement() = default;

public:
    bool operator==(const Placement& other) const;
    bool operator!=(const Placement& other) const;
};

#endif
