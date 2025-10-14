#ifndef PLACEMENT_H
#define PLACEMENT_H


#include <vector>
#include "Cell/Cell/Cell.h"
#include "Cell/CellLocation/CellLocation.h"
#include "Index/Coordinate/Coordinate.h"

class Placement {
private:

protected:
    const std::vector<Cell> placement;

public:
    explicit Placement(std::vector<Cell> placement);
    virtual ~Placement() = default;

public:
	const std::vector<Cell>& getPlacement() const;

public:
    bool operator==(const Placement& other) const;
    bool operator!=(const Placement& other) const;
};

#endif
