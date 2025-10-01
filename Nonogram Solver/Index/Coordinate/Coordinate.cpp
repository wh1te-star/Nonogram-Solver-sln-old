#include "Index/Coordinate/Coordinate.h"
#include "Index/CellIndex/RowIndex.h"
#include "Index/CellIndex/ColumnIndex.h"

Coordinate::Coordinate(RowIndex rowIndex, ColumnIndex columnIndex) :
    rowIndex(rowIndex), columnIndex(columnIndex) {}

bool Coordinate::operator==(const Coordinate& other) const {
	return rowIndex == other.rowIndex && columnIndex == other.columnIndex;
}

bool Coordinate::operator!=(const Coordinate& other) const {
    return !(*this == other);
}

RowIndex Coordinate::getRowIndex() const {
    return rowIndex;
}

ColumnIndex Coordinate::getColumnIndex() const {
    return columnIndex;
}

Coordinate Coordinate::move(int rowShift, int columnShift) const {
    return Coordinate(rowIndex + rowShift, columnIndex + columnShift);
}

