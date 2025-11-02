#include "Placement/Placement/ColumnPlacement.h"
#include "Index/Coordinate/Coordinate.h"
#include "Cell/Cell/Cell.h"
#include "Cell/CellLocation/CellLocation.h"

ColumnPlacement::ColumnPlacement(std::vector<Cell> placement) :
	Placement(placement) {}

const std::vector<CellLocation> ColumnPlacement::getCellLocationList(const Coordinate& coordinate) const {
	std::vector<CellLocation> cellLocationList;
	int shift = 0;
	for(Cell cell : placement) {
		Coordinate cellCoordinate = coordinate.move(shift, 0);
		cellLocationList.emplace_back(cellCoordinate, cell);
		shift++;
	}
	return cellLocationList;
}
