#include "Placement/Placement/ColumnPlacement.h"
#include "Index/Coordinate/Coordinate.h"
#include "Cell/Cell/Cell.h"
#include "Cell/CellLocation/CellLocation.h"

ColumnPlacement::ColumnPlacement(Coordinate coordinate, std::vector<Cell> placement) :
	Placement(coordinate, placement) {}

std::vector<CellLocation> ColumnPlacement::getCellLocationList() {
	std::vector<CellLocation> cellLocationList;
	for (size_t i = 0; i < Placement::placement.size(); i++) {
		Coordinate currentCoordinate = Placement::coordinate.move(0, (int)i);
		Cell cell = Placement::placement[i];
		cellLocationList.emplace_back(currentCoordinate, cell);
	}
	return cellLocationList;
}
