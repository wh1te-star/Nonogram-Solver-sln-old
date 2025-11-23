#include "Placement/Placement/Placement.h"

#include <cassert>
#include "Cell/Cell/Cell.h"
#include "Index/Coordinate/Coordinate.h"
#include "Placement/Placement/RowPlacement.h"
#include "Placement/Placement/ColumnPlacement.h"


Placement::Placement(std::vector<Cell> placement) :
    placement(placement) {
    assert(!hasNone());
}

Placement::Placement(std::string colorString) {
	for (char colorChar : colorString) {
		switch (colorChar) {
		case BLACK_CHAR:
			placement.emplace_back(CellColor::Black);
			break;
		case WHITE_CHAR:
			placement.emplace_back(CellColor::White);
			break;
		default: 
			assert(false);
			break;
		}
	}
}

Placement::Placement(HintNumber hintNumber) {
    for(int i= 0; i < hintNumber.getNumber(); i++) {
        placement.emplace_back(Cell(CellColor::Black));
	}
}


const std::vector<Cell>& Placement::getPlacement() const {
    return placement;
}

bool Placement::operator==(const Placement& other) const {
	return placement == other.placement;
}

bool Placement::operator!=(const Placement& other) const {
    return !(placement == other.placement);
}

Cell Placement::operator[](const CellIndex& index) const {
    return placement[index.getIndex()];
}

Placement Placement::operator+(const Placement& other) const {
    std::vector<Cell> newPlacement;
    newPlacement.reserve(placement.size() + other.placement.size());
    newPlacement.insert(newPlacement.end(), placement.begin(), placement.end());
    newPlacement.insert(newPlacement.end(), other.placement.begin(), other.placement.end());
    return Placement(newPlacement);
}

Placement& Placement::operator+=(const Placement& other) {
    placement.insert(placement.end(), other.placement.begin(), other.placement.end());
    assert(!hasNone()); 
    return *this;
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

const std::vector<CellIndex> Placement::getHintIndex() const {
    std::vector<CellIndex> hintIndexList;
    for (size_t i = 0; i < placement.size(); ++i) {
        if (i <= 0 || placement[i - 1].getColor() != CellColor::Black) {
            if (placement[i].getColor() == CellColor::Black) {
                hintIndexList.emplace_back(static_cast<int>(i));
            }
        }
    }
    return hintIndexList;
}

RowPlacement Placement::toRowPlacement() const {
	return RowPlacement(placement);
}

ColumnPlacement Placement::toColumnPlacement() const {
	return ColumnPlacement(placement);
}

std::ostream& operator<<(std::ostream& os, const Placement& placement) {
    os << "[";
    for (size_t i = 0; i < placement.size(); ++i) {
        os << placement[CellIndex(i)]; 
    }
    os << "]";
    return os;
}
