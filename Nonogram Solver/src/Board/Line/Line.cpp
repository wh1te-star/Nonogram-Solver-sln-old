#include "Board/Line/Line.h"

#include "Cell/Cell/Cell.h"
#include "Index/Coordinate/Coordinate.h"
#include <cassert>


Line::Line(std::vector<Cell> line) :
    line(line) {}

const std::vector<Cell>& Line::getLine() const {
    return line;
}

bool Line::operator==(const Line& other) const {
	return line == other.line;
}

bool Line::operator!=(const Line& other) const {
    return !(*this == other);
}

Cell Line::operator[](const CellIndex& index) const {
    return line[index.getIndex()];
}

const size_t Line::size() const {
    return line.size();
}

const std::vector<CellLocation> Line::getCellLocationList(const Coordinate& coordinate) const {
	std::vector<CellLocation> cellLocationList;
	int shift = 0;
	for(Cell cell : line) {
		Coordinate cellCoordinate = coordinate.move(0, shift);
		cellLocationList.emplace_back(cellCoordinate, cell);
		shift++;
	}
	return cellLocationList;
}
