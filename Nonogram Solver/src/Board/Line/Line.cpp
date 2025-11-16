#include "Board/Line/Line.h"

#include "Cell/Cell/Cell.h"
#include "Index/Coordinate/Coordinate.h"
#include <cassert>


Line::Line(std::vector<Cell> line) :
    line(line) {}

Line::Line(std::string colorString) {
	for (char colorChar : colorString) {
		switch (colorChar) {
		case BLACK_CHAR:
			line.emplace_back(CellColor::Black);
			break;
		case WHITE_CHAR:
			line.emplace_back(CellColor::White);
			break;
		case NONE_CHAR:
			line.emplace_back(CellColor::None);
			break;
		default: 
			assert(false);
			break;
		}
	}
}

const std::vector<Cell>& Line::getLine() const {
    return line;
}

bool Line::operator==(const Line& other) const {
	return line == other.line;
}

bool Line::operator!=(const Line& other) const {
    return !(*this == other);
}

const Cell& Line::operator[](const CellIndex& index) const {
    return line[index.getIndex()]; 
}

Cell& Line::operator[](const CellIndex& index) {
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

bool Line::canPlaceBlock(const CellIndex& startIndex, const HintNumber& hintNumber) const {
	int start = startIndex.getIndex();
	int end = start + hintNumber.getNumber() - 1;
	if (end >= static_cast<int>(line.size())) {
		return false;
	}
	for (int i = start; i <= end; i++) {
		if (!line[i].canColor(CellColor::Black)) {
			return false;
		}
	}
	if (start > 0) {
		if (line[start - 1].getColor() == CellColor::Black) {
			return false;
		}
	}
	if (end + 1 < static_cast<int>(line.size())) {
		if (line[end + 1].getColor() == CellColor::Black) {
			return false;
		}
	}
	return true;
}

std::ostream& operator<<(std::ostream& os, const Line& line) {
    os << "[";
    for (size_t i = 0; i < line.size(); ++i) {
        os << line[CellIndex(i)]; 
    }
    os << "]";
    return os;
}
