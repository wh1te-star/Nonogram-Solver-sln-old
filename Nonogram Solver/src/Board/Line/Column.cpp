#include "Board/Line/Column.h"
#include "Index/Coordinate/Coordinate.h"
#include "Cell/Cell/Cell.h"
#include "Cell/CellLocation/CellLocation.h"

Column::Column(std::vector<Cell> line) :
	Line(line) {}
