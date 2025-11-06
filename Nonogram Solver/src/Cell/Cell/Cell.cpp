#include "Cell/Cell/Cell.h"

#include "Cell/CellColor/CellColor.h"
#include <algorithm>


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
