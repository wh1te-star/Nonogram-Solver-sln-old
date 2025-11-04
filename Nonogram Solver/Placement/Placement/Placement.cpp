#include "Placement/Placement/Placement.h"

#include "Cell/Cell/Cell.h"
#include "Index/Coordinate/Coordinate.h"
#include <cassert>


Placement::Placement(std::vector<Cell> placement) :
    placement(placement) {
    assert(!hasNone());
}

const std::vector<Cell>& Placement::getPlacement() const {
    return placement;
}

bool Placement::operator==(const Placement& other) const {
	return placement == other.placement;
}

bool Placement::operator!=(const Placement& other) const {
    return !(*this == other);
}

Cell Placement::operator[](const CellIndex& index) const {
    return placement[index.getIndex()];
}

bool Placement::hasNone() const {
    bool hasNoneColor = false;
    for (Cell cell : placement) {
        if(cell.getColor() == CellColor::None) {
            hasNoneColor = true;
            break;
		}
    }
	return hasNoneColor;
}

const size_t Placement::size() const {
    return placement.size();
}

const std::vector<CellLocation> Placement::getCellLocationList(const Coordinate& coordinate) const {
	std::vector<CellLocation> cellLocationList;
	int shift = 0;
	for(Cell cell : placement) {
		Coordinate cellCoordinate = coordinate.move(0, shift);
		cellLocationList.emplace_back(cellCoordinate, cell);
		shift++;
	}
	return cellLocationList;
}
