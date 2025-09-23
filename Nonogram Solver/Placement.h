#ifndef PLACEMENT_H
#define PLACEMENT_H


#include <vector>
#include "Cell.h"
#include "Orientation.h"

class Placement {
private:
    std::vector<Cell> placement;

    bool operator==(const Placement& other) const;
    bool operator!=(const Placement& other) const;

public:
    explicit Placement(std::vector<Cell> placement);
};

#endif
