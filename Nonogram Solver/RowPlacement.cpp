#include "RowPlacement.h"
#include "Coordinate.h"

RowPlacement::RowPlacement(Coordinate coordinate, std::vector<Cell> placement) :
	Placement(coordinate, placement) {}

std::vector<CellLocation> RowPlacement::getCellLocationList() {
	std::vector<CellLocation> cellLocationList;
	for (size_t i = 0; i < Placement::placement.size(); i++) {
		Coordinate currentCoordinate = Placement::coordinate.move(0, (int)i);
		Cell cell = Placement::placement[i];
		cellLocationList.emplace_back(currentCoordinate, cell);
	}
	return cellLocationList;
}
