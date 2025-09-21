#include "line.h"
#include "Cell.h"

Line::Line(Orientation orientation, std::vector<Cell> line) :
	orientation(orientation), line(line) {}

bool Line::operator==(const Line& other) const {
	return orientation == other.orientation && line == other.line;
}

bool Line::operator!=(const Line& other) const {
    return !(*this == other);
}

