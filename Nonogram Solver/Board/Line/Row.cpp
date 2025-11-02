#include "Placement/Placement/RowPlacement.h"
#include "Index/Coordinate/Coordinate.h"
#include "Cell/Cell/Cell.h"
#include "Cell/CellLocation/CellLocation.h"

RowPlacement::RowPlacement(std::vector<Cell> placement) :
	Placement(placement) {}

const std::vector<CellLocation> RowPlacement::getCellLocationList(const Coordinate& coordinate) const {
	std::vector<CellLocation> cellLocationList;
	int shift = 0;
	for(Cell cell : placement) {
		Coordinate cellCoordinate = coordinate.move(0, shift);
		cellLocationList.emplace_back(cellCoordinate, cell);
		shift++;
	}
	return cellLocationList;
}
