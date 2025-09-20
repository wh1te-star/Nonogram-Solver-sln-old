#include "Coordinate.h"

Coordinate::Coordinate(RowIndex rowIndex, ColumnIndex columnIndex) :
    rowIndex(rowIndex), columnIndex(columnIndex) {}

Coordinate Coordinate::move(int rowShift, int columnShift) const {
    return Coordinate(rowIndex + rowShift, columnIndex + columnShift);
}

