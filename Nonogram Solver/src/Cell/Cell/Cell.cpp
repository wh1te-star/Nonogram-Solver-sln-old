#include "Cell/Cell/Cell.h"

#include <algorithm>
#include <cassert>
#include "Cell/CellColor/CellColor.h"


Cell::Cell() : color(None) {}

Cell::Cell(CellColor color) :
    color(std::move(color)) {}

const CellColor& Cell::getColor() const {
    return color;
}

bool Cell::operator==(const Cell& other) const {
    return color == other.color;
}

bool Cell::operator!=(const Cell& other) const {
	return !(*this == other);
}

bool Cell::canColor(const CellColor& newColor) const {
    if (color == None) {
        return true;
    }
    return color == newColor;
}

std::ostream& operator<<(std::ostream& os, const Cell& cell) {
    switch (cell.getColor()) {
        case CellColor::Black: 
            os << "B"; 
            break;
        case CellColor::White: 
            os << "W"; 
            break;
        case CellColor::None:  
			os << ".";
            break;
        default: 
            assert(false);
            break;
    }
    return os;
}

