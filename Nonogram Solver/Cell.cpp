#include "Cell.h"

Cell::Cell() : color(None) {}

Cell::Cell(CellColor color) : color(color) {}

CellColor Cell::get() const {
    return color;
}

bool Cell::operator==(const Cell& other) const {
    return color == other.color;
}

bool Cell::operator!=(const Cell& other) const {
	return !(*this == other);
}

bool Cell::canColor(CellColor newColor) const {
    if (color == None) {
        return true;
    }
    return color == newColor;
}
